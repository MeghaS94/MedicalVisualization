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
//#include <vtkIdType.h>
#include <vtkCellLinks.h>
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
                if(pixel2>=isovalue_start && pixel2<=isovalue_end)
                    modifiedData->SetScalarComponentFromFloat(x,y,z,0,1.0);
                else
                    modifiedData->SetScalarComponentFromFloat(x,y,z,0,0.0);
            }
        }
    }

    surface->SetInputData(modifiedData);
    surface->ComputeNormalsOn();
    surface->SetValue(0, 0.5);
    surface->GenerateTrianglesOn();

    //confilter->SetInputConnection(surface->GetOutputPort());
    //confilter->SetExtractionModeToLargestRegion();
    //confilter->Update();


    polyArray = surface->GetOutput()->GetPolys();
    polyArray->InitTraversal();

    vtkIdType npts; vtkIdType *pts;

    int count_not3 =0;
    int count_3 =0;
    while(polyArray->GetNextCell(npts, pts))
    {
       if(npts != 3)
            {
           count_not3 +=1;
                }
        else if (npts == 3)
            {
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
}

void VTKSurface::findConnectedVertsRecur(vtkIdType ID)
{
    //maybe you should do a malloc?
    vtkIdType *connectedCells;

    vtkIdType npts; vtkIdType *pts;

    //find cell links and call recursion on them
    connectedCells = cellLinksFilter->GetCells(ID);
    int num_of_cells = cellLinksFilter->GetNcells(ID);
    //vector to perform set operation on
    set<vtkIdType> all_connected_cells;

    for(int j=0;j<num_of_cells;j++)
    {
        polyArray->GetCell(connectedCells[j], npts, pts );
        all_connected_cells.insert(pts[0]);
        all_connected_cells.insert(pts[1]);
        all_connected_cells.insert(pts[2]);
    }

    std::set<vtkIdType>::iterator it;
    for (it = all_connected_cells.begin(); it != all_connected_cells.end(); ++it)
    {
        vtkIdType vertexID = *it;
        if (Array[vertexID] == false)
        {
            Array[vertexID] = true;
            findConnectedVertsRecur(vertexID);
        }

    }

    //call recursion on every pointID in connectedCells
}


void VTKSurface::makeConnectedSurfaces()
{

    //map-> Array

    for(int i=0;i < surface->GetOutput()->GetNumberOfPoints();i++)
    {
        if(Array[i] == false )
        {
            Array[i] = true;
            //call recursion on every pointID in connectedCells
            cout << "new surface" << endl;
            findConnectedVertsRecur(i);
        }
    }

}

void VTKSurface::render(Window *window)
{
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(surface->GetOutputPort());
    mapper->ScalarVisibilityOff();

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    //actor.SetNumberOfCloudPoints( 1000000 );
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(red, blue, green);
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    //renderer->SetBackground(.1, .2, .3);
    renderer->AddActor(actor);

    ((VTKWindow*)window)->getWidget()->GetRenderWindow()->AddRenderer(renderer);
    renderer->SetBackground(.0, .0, .0);
    renderer->ResetCamera();
}



