
#include <vtkActor.h>
#include <vtkMarchingContourFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkProperty.h>
#include <vtkContourFilter.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkCellLinks.h>
#include <vtkFillHolesFilter.h>
#include <vtkPolyDataNormals.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include "vtksurface.h"
#include "window.h"
#include "vtkwindow.h"


VTKSurface::VTKSurface(double isoValue_start, double isoValue_end) : Surface(isoValue_start, isoValue_end)
{
    //this constructor is not being used anywhere
    modifiedData = vtkSmartPointer<vtkImageData>::New();
    //could use vtk contour filter to get iso-surfaces from ranges
    //surface = vtkSmartPointer<vtkMarchingCubes>::New();
    surface = vtkSmartPointer<vtkContourFilter>::New();
    surface->SetNumberOfContours(1);
    polyArray = vtkSmartPointer<vtkCellArray>::New();
    cellLinksFilter = vtkSmartPointer<vtkCellLinks>::New();

}

VTKSurface::VTKSurface(double isoValue_start, double isoValue_end, float r, float g, float b) : Surface(isoValue_start, isoValue_end)
{
    modifiedData = vtkSmartPointer<vtkImageData>::New();
    //could use vtk contour filter to get iso-surfaces from ranges
    //surface = vtkSmartPointer<vtkMarchingCubes>::New();
    surface = vtkSmartPointer<vtkContourFilter>::New();
    //confilter = vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
    surface->SetNumberOfContours(1);
    red = r; blue = b; green =g;
    polyArray = vtkSmartPointer<vtkCellArray>::New();
    surfacePolygons = vtkSmartPointer<vtkPolyData>::New();
    wholeSurfacePolygons = vtkSmartPointer<vtkPolyData>::New();
    cellLinksFilter = vtkSmartPointer<vtkCellLinks>::New();
    renderer = vtkSmartPointer<vtkRenderer>::New();
    count = 0;
    current_surface = 0;
    whole = true;
    threshold = 5000;
    data[0] = vtkSmartPointer<vtkPolyData>::New();
    data[1] = vtkSmartPointer<vtkPolyData>::New();
    celldata[0] = vtkSmartPointer<vtkCellArray>::New();
    celldata[1] = vtkSmartPointer<vtkCellArray>::New();
    small=0;
    big=0;
    actor = vtkSmartPointer<vtkActor>::New();
    actor1 = vtkSmartPointer<vtkActor>::New();
    actor2 = vtkSmartPointer<vtkActor>::New();
    mapper1 = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper2 = vtkSmartPointer<vtkPolyDataMapper>::New();
}

void VTKSurface::setLayers(Layer* layers, int n) {
    this->layers = layers;
    numberOfLayers = n;
}
/*void VTKSurface::readData(string foldername)
{
    reader->SetDirectoryName(foldername.c_str());
    reader->Update();
    volume->DeepCopy(reader->GetOutput());
}*/

void VTKSurface::setImageData(ImageData* data) {
    imageData = (VTKImageData*) data;
    imageData->getImageData()->GetExtent(extent);
    imageData->getImageData()->GetBounds(bounds);
}

void VTKSurface::createSurface()
{
    modifiedData->DeepCopy(imageData->getImageData());
    for(int x=extent[0];x<=extent[1];x++) {
        for(int y=extent[2];y<=extent[3];y++) {
            for(int z=extent[4];z<=extent[5];z++) {
                //double* pixel =  static_cast<double*>(data->GetOutput()->GetScalarComponentAsFloat(x,y,z,1));
                //float* pixel1 = static_cast<float*>(modifiedData->GetScalarPointer(x,y,z));
                float pixel2 =  (imageData->getImageData()->GetScalarComponentAsFloat(x,y,z,0));
                //cout  << "x: " << extent[0] << "x: " << extent[1] << " y: " << extent[2] << " y: " << extent[3] << " z: " << extent[4] << " z: " << extent[5] << endl;
                /*if(pixel2>=isovalue_start && pixel2<=isovalue_end)
                    modifiedData->SetScalarComponentFromFloat(x,y,z,0,1.0);
                else
                    modifiedData->SetScalarComponentFromFloat(x,y,z,0,0.0);*/
                modifiedData->SetScalarComponentFromFloat(x,y,z,0,0.0);
                for(int i=0; i<numberOfLayers; i++) {
                    if(layers[i].on && pixel2>=layers[i].isovalueStart && pixel2<=layers[i].isovalueEnd) {
                        modifiedData->SetScalarComponentFromFloat(x,y,z,0,1.0);
                        break;
                    }
                }
            }
        }
    }

    surface->ComputeNormalsOn();
    surface->GenerateTrianglesOn();
    surface->SetInputData(modifiedData);
    surface->SetValue(0, 0.5);

    //confilter->SetInputConnection(surface->GetOutputPort());
    //confilter->SetExtractionModeToLargestRegion();
    //confilter->Update();

}

long VTKSurface::findConnectedVertsRecur(vtkIdType ID)
{
    vector <vtkIdType> all_connected_cells;
    all_connected_cells.push_back(ID);
    int i=0;
    while(i<all_connected_cells.size()) {
        //cout << all_connected_cells[i] << endl;
        int num_of_cells = cellLinksFilter->GetNcells(all_connected_cells[i]);
        vtkIdType *connectedCells;
        vtkIdType npts; vtkIdType *pts;
        //find cell links and call recursion on them
        connectedCells = cellLinksFilter->GetCells(all_connected_cells[i]);
        //surface->GetOutput()->GetPointCells(all_connected_cells[i], num_of_cells, connectedCells );
        for(int j=0;j<num_of_cells;j++)
        {
            surface->GetOutput()->GetCellPoints(connectedCells[j], npts, pts );
            //surface->GetOutput()->GetCellPoints(connectedCells[j], npts, pts );
            //if(!Array2[connectedCells[j]]) {
                subsurfaces.push_back(pts);
            //    Array2[connectedCells[j]]=true;
            //}
            if(!Array[pts[0]]) {
                Array[pts[0]]=true;
                all_connected_cells.push_back(pts[0]);
            }
            if(!Array[pts[1]]) {
                Array[pts[1]]=true;
                all_connected_cells.push_back(pts[1]);
            }
            if(!Array[pts[2]]) {
                Array[pts[2]]=true;
                all_connected_cells.push_back(pts[2]);
            }
        }
        i++;
    }
    return all_connected_cells.size();
}

void VTKSurface::makeConnectedSurfaces()
{

    //map-> Array
    cellLinksFilter->Allocate(surface->GetOutput()->GetNumberOfPoints());
    cellLinksFilter->BuildLinks(surface->GetOutput(), polyArray);
    for(int i=0;i < surface->GetOutput()->GetNumberOfPoints();i++)
    {
        if(Array[i] == false )
        {
            Array[i] = true;
            //call recursion on every pointID in connectedCells
            subsurfaces.clear();
            long c = findConnectedVertsRecur(i);
            createConnectedSurfaces();
        }
    }
}

void VTKSurface::showCompleteSurface() {
    whole = true;
    surfacePolygons->SetPolys(polyArray);
    surface->Update();
    actor1->GetProperty()->SetOpacity(1.0);
    actor2->GetProperty()->SetOpacity(1.0);
    actor->VisibilityOff();
    renderer->GetRenderWindow()->Render();
}

void VTKSurface::showComponentSurface() {
    whole = false;
    surfacePolygons->SetPolys(connectedComponents[current_surface]);
    surface->Update();
    if(surface->GetOutput()->GetPolys()->GetNumberOfCells()>threshold)
        actor->GetProperty()->SetColor(red, blue, green);
    else
        actor->GetProperty()->SetColor(1.0, 0.0, 0.0);
    actor1->GetProperty()->SetOpacity(0.1);
    actor2->GetProperty()->SetOpacity(0.1);
    actor->VisibilityOn();
    renderer->GetRenderWindow()->Render();
}

void VTKSurface::showNextSurface() {
    current_surface += 1;
    if(current_surface>=connectedComponents.size())
        current_surface = 0;
}

void VTKSurface::showPreviousSurface() {
    current_surface -= 1;
    if(current_surface<0)
        current_surface = connectedComponents.size()-1;
}

int VTKSurface::getCurrentSurface() {
    return current_surface+1;
}

long VTKSurface::getMinimum() {
    long mini = 10000000;
    for(int i=0; i<connectedComponents.size(); i++) {
        if(connectedComponents[i]->GetNumberOfCells()<mini)
            mini=connectedComponents[i]->GetNumberOfCells();
    }
    return mini;
}

long VTKSurface::getMaximum() {
    long maxi = 0;
    for(int i=0; i<connectedComponents.size(); i++) {
        if(connectedComponents[i]->GetNumberOfCells()>maxi)
            maxi=connectedComponents[i]->GetNumberOfCells();
    }
    return maxi;
}

void VTKSurface::updateThreshold(int val) {
    threshold = val;
    vtkIdType npts; vtkIdType *pts;
    big=0;
    small=0;
    cout << "here1 " << val << " " << threshold << endl;
    for(int i=0; i<connectedComponents.size(); i++) {
        if(connectedComponents[i]->GetNumberOfCells()>threshold)
            big+=connectedComponents[i]->GetNumberOfCells();
        else
            small+=connectedComponents[i]->GetNumberOfCells();
    }

    cout << big << endl;
    cout << small << endl;

    celldata[0]->Allocate(celldata[0]->EstimateSize(big, 3));
    celldata[1]->Allocate(celldata[1]->EstimateSize(small, 3));

    //cout << connectedComponents.size() << endl;
    //vtkIdType npts; vtkIdType *pts;
    for(int i=0; i<connectedComponents.size(); i++) {
        if(connectedComponents[i]->GetNumberOfCells()>threshold) {
            while(connectedComponents[i]->GetNextCell(npts, pts))
                celldata[0]->InsertNextCell(npts, pts);
        }
        else {
            while(connectedComponents[i]->GetNextCell(npts, pts))
                celldata[1]->InsertNextCell(npts, pts);
        }
    }

    cout << celldata[0]->GetNumberOfCells() << endl;
    cout << celldata[1]->GetNumberOfCells() << endl;

    data[0]->SetPolys(celldata[0]);
    data[1]->SetPolys(celldata[1]);
    mapper1->SetInputData(data[0]);
    mapper2->SetInputData(data[1]);
    renderer->GetRenderWindow()->Render();
}

long VTKSurface::getNumberOfTriangles(bool status) {
    if(status)
        return polyArray->GetNumberOfCells();
    else
        return connectedComponents[current_surface]->GetNumberOfCells();
}

void VTKSurface::createConnectedSurfaces()
{
    vtkSmartPointer<vtkCellArray> temp = vtkSmartPointer<vtkCellArray>::New();
    vtkIdType s = temp->EstimateSize(subsurfaces.size(), 3);
    temp->Allocate(s);
    for(int i=0;i < subsurfaces.size();i++)
    {
        temp->InsertNextCell(3, subsurfaces[i]);
    }
    connectedComponents.push_back(temp);
    if(temp->GetNumberOfCells()>threshold)
        big += temp->GetNumberOfCells();
    else
        small += temp->GetNumberOfCells();
}

void VTKSurface::render(Window *window)
{
    ((VTKWindow*)window)->getWidget()->GetRenderWindow()->AddRenderer(renderer);
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(surface->GetOutputPort());
    mapper->ScalarVisibilityOff();

    //actor.SetNumberOfCloudPoints( 1000000 );
    actor->SetMapper(mapper);
    //vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    //renderer->SetBackground(.1, .2, .3);

    renderer->AddActor(actor);
    cout << "here2" << endl;

    renderer->SetBackground(.0, .0, .0);
    renderer->ResetCamera();

    polyArray->DeepCopy(surface->GetOutput()->GetPolys());
    polyArray->InitTraversal();

    surface->GetOutput()->BuildCells();
    surface->GetOutput()->BuildLinks();

    surfacePolygons = surface->GetOutput();
    wholeSurfacePolygons->DeepCopy(surface->GetOutput());

    vtkIdType npts; vtkIdType *pts;

    int count_not3 =0;
    int count_3 =0;
    while(polyArray->GetNextCell(npts, pts))
    {
        if(npts != 3) {
           count_not3 +=1;
        }
        else if (npts == 3) {
            count_3 +=1;
        }
    }

    cout << "count of npts not 3 : " << count_not3 << endl;
    cout << "count of npts 3 : " << count_3 << endl;
    //confilter->GetOutput()->GenerateTrianglesOn();
    cout <<  " Num of triangles : "<< surface->GetOutput()->GetNumberOfStrips() << endl;
    cout <<  " Num of polys : "<< surface->GetOutput()->GetNumberOfPolys() << endl;
    //cout <<  " Num of strips : "<< confilter->GetOutput()->GetNumberOfStrips() << endl;

    cout <<  " Num of points : "<< surface->GetOutput()->GetNumberOfPoints() << endl;

    makeConnectedSurfaces();
    //surface->update();
    actor->VisibilityOff();

    celldata[0]->Allocate(celldata[0]->EstimateSize(big, 3));
    celldata[1]->Allocate(celldata[1]->EstimateSize(small, 3));

    cout << connectedComponents.size() << endl;
    //vtkIdType npts; vtkIdType *pts;
    for(int i=0; i<connectedComponents.size(); i++) {
        if(connectedComponents[i]->GetNumberOfCells()>threshold) {
            while(connectedComponents[i]->GetNextCell(npts, pts))
                celldata[0]->InsertNextCell(npts, pts);
        }
        else {
            while(connectedComponents[i]->GetNextCell(npts, pts))
                celldata[1]->InsertNextCell(npts, pts);
        }
    }
    cout << celldata[0]->GetNumberOfCells() << endl;
    cout << celldata[1]->GetNumberOfCells() << endl;
    data[0]->DeepCopy(wholeSurfacePolygons);
    data[1]->DeepCopy(wholeSurfacePolygons);
    data[0]->SetPolys(celldata[0]);
    data[1]->SetPolys(celldata[1]);
    mapper1->SetInputData(data[0]);
    mapper1->ScalarVisibilityOff();
    actor1->SetMapper(mapper1);
    actor1->GetProperty()->SetColor(red, blue, green);
    actor1->GetProperty()->SetOpacity(1.0);
    mapper2->SetInputData(data[1]);
    mapper2->ScalarVisibilityOff();
    actor2->SetMapper(mapper2);
    actor2->GetProperty()->SetColor(1.0, 0.0, 0.0);
    actor2->GetProperty()->SetOpacity(1.0);
    renderer->AddActor(actor1);
    renderer->AddActor(actor2);
}



