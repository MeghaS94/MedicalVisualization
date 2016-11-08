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
#include <vtkUnsignedCharArray.h>
#include <vtkFillHolesFilter.h>
#include <vtkPolyDataNormals.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkVectorText.h>
#include "vtksurface.h"
#include "window.h"
#include "vtkwindow.h"

vector<Annotation> Annotations;

//should be called on button click to enable annotations
// Define interaction style
class MouseInteractorStylePP : public vtkInteractorStyleTrackballCamera
{
  public:
    /*
    vtkSmartPointer<vtkActor> actor3;
    vtkSmartPointer<vtkPolyDataMapper> mapper3;
*/

  /*  vtkSmartPointer<vtkPolyData> pointsPolydata;
    vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter;
    vtkSmartPointer<vtkPolyData> polydata;
    vtkSmartPointer<vtkUnsignedCharArray> colors;
*/
    static MouseInteractorStylePP* New();
    vtkTypeMacro(MouseInteractorStylePP, vtkInteractorStyleTrackballCamera);
    //vtkSmartPointer<vtkPolyData> pointsPolydata = vtkSmartPointer<vtkPolyData>::New();

    virtual void OnLeftButtonDown()
    {
      std::cout << "Picking pixel: " << this->Interactor->GetEventPosition()[0] << " " << this->Interactor->GetEventPosition()[1] << std::endl;
      this->Interactor->GetPicker()->Pick(this->Interactor->GetEventPosition()[0],
                         this->Interactor->GetEventPosition()[1],
                         0,  // always zero.
                         this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
      double picked[3];
      this->Interactor->GetPicker()->GetPickPosition(picked);
      std::cout << "Picked value: " << picked[0] << " " << picked[1] << " " << picked[2] << std::endl;
      //points->InsertNextPoint (picked[0], picked[1], picked[2]);
      Annotation a;
      a.x = picked[0] ;
      a.y = picked[1] ;
      a.z = picked[2] ;
      a.text = "string";
      a.r = 0.0;
      a.g = 0.0;
      a.b = 255.0;
      //cout << a.text << endl;
      Annotations.push_back(a);

      //colors->SetNumberOfComponents(3);
      //colors->SetName ("Colors");
      //unsigned char green[3] = {0, 255, 0};
      //colors->InsertNextTupleValue(green);
      //colors->InsertNextTupleValue(green);
      //colors->InsertNextTupleValue(blue);
      for(int i=0;i<Annotations.size();i++)
      {
      vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
      sphereSource->SetCenter(Annotations[i].x, Annotations[i].y , Annotations[i].z /*picked[0], picked[1], picked[2]*/);
      sphereSource->SetRadius(5.0);
      vtkSmartPointer<vtkPolyDataMapper> mapper4 = vtkSmartPointer<vtkPolyDataMapper>::New();
      vtkSmartPointer<vtkActor> actor4 = vtkSmartPointer<vtkActor>::New();
      mapper4->SetInputConnection(sphereSource->GetOutputPort());
      actor4->SetMapper(mapper4);

      this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(actor4);

      //text
      vtkSmartPointer<vtkTextActor> textActor = vtkSmartPointer<vtkTextActor>::New();
      textActor->SetInput ( "Hello world" );
      textActor->SetPosition2 ( 10, 40 );
      textActor->GetTextProperty()->SetFontSize ( 24 );
      textActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
      this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor ( textActor );

      }

      //for(int i=0;i<Annotations.size();i++)
      //{
      //points->InsertNextPoint (picked[0], picked[1], picked[2]);
      //unsigned char color[3] = {0.0, 0.0, 255.0};//{Annotations[i].r, Annotations[i].g, Annotations[i].b};
      //unsigned char color[3] = {0.0, 0.0, 1.0};
      //colors->InsertNextTupleValue(color);
      //}
      //pointsPolydata->SetPoints(points);
      //vertexFilter->SetInputData(pointsPolydata);
      //vertexFilter->Update();
      //polydata->ShallowCopy(vertexFilter->GetOutput());
      //polydata->GetPointData()->SetScalars(colors);

      //mapper3->SetInputData(polydata);
      //mapper3->SetInputConnection(sphereSource->GetOutputPort());
      //actor3->SetMapper(mapper3);
      //this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(actor3);
      //actor3->GetProperty()->SetPointSize(15);

      // Forward events
      cout << Annotations.size() << endl;
      //cout << "first time : " << Annotations[0].x << ", " << Annotations[0].y << ", " << Annotations[0].z << endl;
      vtkInteractorStyleTrackballCamera::OnLeftButtonDown();

      //pointsPolydata->SetPoints(points);
    }

};

vtkStandardNewMacro(MouseInteractorStylePP);



class MouseInteractorStyleDoubleClick : public vtkInteractorStyleTrackballCamera
{
  public:

    static MouseInteractorStyleDoubleClick* New();
    vtkTypeMacro(MouseInteractorStyleDoubleClick, vtkInteractorStyleTrackballCamera);

    MouseInteractorStyleDoubleClick() : NumberOfClicks(0), ResetPixelDistance(5)
    {
      this->PreviousPosition[0] = 0;
      this->PreviousPosition[1] = 0;
    }

    virtual void OnLeftButtonDown()
    {
      //std::cout << "Pressed left mouse button." << std::endl;
      this->NumberOfClicks++;
      //std::cout << "NumberOfClicks = " << this->NumberOfClicks << std::endl;
      int pickPosition[2];
      this->GetInteractor()->GetEventPosition(pickPosition);

      int xdist = pickPosition[0] - this->PreviousPosition[0];
      int ydist = pickPosition[1] - this->PreviousPosition[1];

      this->PreviousPosition[0] = pickPosition[0];
      this->PreviousPosition[1] = pickPosition[1];

      int moveDistance = (int)sqrt((double)(xdist*xdist + ydist*ydist));

      // Reset numClicks - If mouse moved further than resetPixelDistance
      if(moveDistance > this->ResetPixelDistance)
        {
        this->NumberOfClicks = 1;
        }


      if(this->NumberOfClicks == 2)
        {
        std::cout << "Double clicked." << std::endl;
        this->NumberOfClicks = 0;
        std::cout << "Picking pixel: " << this->Interactor->GetEventPosition()[0] << " " << this->Interactor->GetEventPosition()[1] << std::endl;
        this->Interactor->GetPicker()->Pick(this->Interactor->GetEventPosition()[0],
                           this->Interactor->GetEventPosition()[1],
                           0,  // always zero.
                           this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
        double picked[3];
        this->Interactor->GetPicker()->GetPickPosition(picked);
        std::cout << "Picked value: " << picked[0] << " " << picked[1] << " " << picked[2] << std::endl;
        //points->InsertNextPoint (picked[0], picked[1], picked[2]);
        Annotation a;
        a.x = picked[0] ;
        a.y = picked[1] ;
        a.z = picked[2] ;
        a.text = "string";
        a.r = 0.0;
        a.g = 0.0;
        a.b = 255.0;
        //cout << a.text << endl;
        Annotations.push_back(a);

        //colors->SetNumberOfComponents(3);
        //colors->SetName ("Colors");
        //unsigned char green[3] = {0, 255, 0};
        //colors->InsertNextTupleValue(green);
        //colors->InsertNextTupleValue(green);
        //colors->InsertNextTupleValue(blue);
            for(int i=0;i<Annotations.size();i++)
            {
            vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
            sphereSource->SetCenter(Annotations[i].x, Annotations[i].y , Annotations[i].z /*picked[0], picked[1], picked[2]*/);
            sphereSource->SetRadius(5.0);
            vtkSmartPointer<vtkPolyDataMapper> mapper4 = vtkSmartPointer<vtkPolyDataMapper>::New();
            vtkSmartPointer<vtkActor> actor4 = vtkSmartPointer<vtkActor>::New();
            mapper4->SetInputConnection(sphereSource->GetOutputPort());
            actor4->SetMapper(mapper4);
            this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(actor4);

            //text
            /*vtkSmartPointer<vtkTextActor> textActor = vtkSmartPointer<vtkTextActor>::New();
            textActor->SetInput ( "Hello world" );
            textActor->SetPosition2 ( 10, 40 );
            textActor->GetTextProperty()->SetFontSize ( 24 );
            textActor->GetTextProperty()->SetColor ( 1.0, 0.0, 0.0 );
            */
            vtkSmartPointer<vtkVectorText> textSource = vtkSmartPointer<vtkVectorText>::New();
            textSource->SetText("Hello");
            textSource->Update();
            // Create a mapper and actor
            vtkSmartPointer<vtkPolyDataMapper> mapper_text = vtkSmartPointer<vtkPolyDataMapper>::New();
            mapper_text->SetInputConnection(textSource->GetOutputPort());
            vtkSmartPointer<vtkActor> actor_text = vtkSmartPointer<vtkActor>::New();
            actor_text->SetMapper(mapper_text);
            actor_text->GetProperty()->SetColor(255.0, 0.0, 0.0);
            actor_text->SetPosition(Annotations[i].x, Annotations[i].y+2.0, Annotations[i].z  );
            actor_text->SetOrientation(0.0, 0.0, 1.0);
            actor_text->SetScale(14.0);
            this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor ( actor_text );
            }
        }
      // forward events
      vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    }

  private:
    unsigned int NumberOfClicks;
    int PreviousPosition[2];
    int ResetPixelDistance;
};
vtkStandardNewMacro(MouseInteractorStyleDoubleClick);

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
                if(x>extent[0] && x<extent[1] && y>extent[2] && y<extent[3] && z>extent[4] && z<extent[5]) {
                    for(int i=0; i<numberOfLayers; i++) {
                        if(layers[i].on && pixel2>=layers[i].isovalueStart && pixel2<=layers[i].isovalueEnd) {
                            modifiedData->SetScalarComponentFromFloat(x,y,z,0,1.0);
                            break;
                        }
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
            if(!Array2[connectedCells[j]]) {
                subsurfaces.push_back(pts);
                Array2[connectedCells[j]]=true;
            }
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
    sort(connectedComponents.begin(), connectedComponents.end(), compareFunc());
    vtkIdType npts; vtkIdType *pts;
    for(int i=0; i<connectedComponents.size(); i++) {
        connectedComponents[i]->InitTraversal();
        map<QString, int> edgeCount;
        while(connectedComponents[i]->GetNextCell(npts, pts)) {
            QString edge1, edge2, edge3;
            if(pts[0]  < pts[1] ) {
                QString num1, num2;
                num1.setNum(pts[0] );
                num2.setNum(pts[1] );
                edge1 = num1 + num2;
            }
            else {
                QString num1, num2;
                num1.setNum(pts[1] );
                num2.setNum(pts[0] );
                edge1 = num1 + num2;
            }
            edgeCount[edge1] +=1 ;
            if(pts[1]  < pts[2] ) {
                QString num1, num2;
                num1.setNum(pts[1] );
                num2.setNum(pts[2] );
                edge2 = num1 + num2;
            }
            else {
                QString num1, num2;
                num1.setNum(pts[2] );
                num2.setNum(pts[1] );
                edge2 = num1 + num2;
            }
            edgeCount[edge2] +=1;
            if(pts[0]  < pts[2] )
            {
                QString num1, num2;
                num1.setNum(pts[0] );
                num2.setNum(pts[2] );
                edge3 = num1 + num2;
            }
            else
            {
                QString num1, num2;
                num1.setNum(pts[2] );
                num2.setNum(pts[0] );
                edge3 = num1 + num2;
            }
            edgeCount[edge3] +=1;
        }

        int numOfOpenEdges = 0;
        typedef std::map<QString, int>::iterator it;
        for(it iterator = edgeCount.begin(); iterator != edgeCount.end(); iterator++ ) {
            // iterator->first = key
           // iterator->second = value
           if (iterator->second < 2)
                numOfOpenEdges  +=1;
        }
        numberOfOpenEdges.push_back(numOfOpenEdges);
    }
}

void VTKSurface::showCompleteSurface() {
    whole = true;
    surfacePolygons->SetPolys(polyArray);
    surface->Update();
    actor1->GetProperty()->SetOpacity(1.0);
    actor2->GetProperty()->SetOpacity(1.0);
    actor1->GetProperty()->SetColor(red, blue, green);
    actor2->GetProperty()->SetColor(1.0, 0.0, 0.0);
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
    actor1->GetProperty()->SetColor(red, blue, green);
    actor2->GetProperty()->SetColor(1.0, 0.0, 0.0);
    actor->VisibilityOn();
    renderer->GetRenderWindow()->Render();
}

void VTKSurface::showNextSurface() {
    current_surface += 1;
    if(current_surface>=connectedComponents.size())
        current_surface = 0;
    cout << "surfaceId, numOfOpenEdges "<< current_surface << " , " <<numberOfOpenEdges[current_surface ] << endl;
}

void VTKSurface::showPreviousSurface() {
    current_surface -= 1;
    if(current_surface<0)
        current_surface = connectedComponents.size()-1;
    cout << "surfaceId, numOfOpenEdges "<< current_surface << " , " <<numberOfOpenEdges[current_surface ] << endl;
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
        connectedComponents[i]->InitTraversal();
        if(connectedComponents[i]->GetNumberOfCells()>threshold)
            big+=connectedComponents[i]->GetNumberOfCells();
        else
            small+=connectedComponents[i]->GetNumberOfCells();
    }

    cout << big << endl;
    cout << small << endl;

    //celldata[0]->Allocate(celldata[0]->EstimateSize(big, 3));
    //celldata[1]->Allocate(celldata[1]->EstimateSize(small, 3));
    //celldata[0] = vtkSmartPointer<vtkCellArray>::New();
    //celldata[1] = vtkSmartPointer<vtkCellArray>::New();
    //celldata[0]->Initialize();
    //celldata[1]->Initialize();
    celldata[0]->Reset();
    celldata[1]->Reset();
    celldata[0] = vtkSmartPointer<vtkCellArray>::New();
    celldata[1] = vtkSmartPointer<vtkCellArray>::New();
    celldata[0]->Allocate(celldata[0]->EstimateSize(big+1, 3));
    celldata[1]->Allocate(celldata[1]->EstimateSize(small+1, 3));

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
    vtkIdType temppts[] = {0,0,0};
    celldata[0]->InsertNextCell(npts, temppts);
    celldata[1]->InsertNextCell(npts, temppts);
    cout << celldata[0]->GetNumberOfCells() << endl;
    cout << celldata[1]->GetNumberOfCells() << endl;

    data[0]->SetPolys(celldata[0]);
    data[1]->SetPolys(celldata[1]);
    renderer->GetRenderWindow()->Render();
}

void VTKSurface::removeSurfaces() {
    int i=0;
    while(i<connectedComponents.size() && connectedComponents[i]->GetNumberOfCells()>threshold)
        i++;
    connectedComponents.erase (connectedComponents.begin()+i,connectedComponents.end());
    numberOfOpenEdges.erase (numberOfOpenEdges.begin()+i,numberOfOpenEdges.end());
    updateThreshold(threshold);
}

void VTKSurface::removeSurface() {
    connectedComponents.erase (connectedComponents.begin()+current_surface);
    numberOfOpenEdges.erase (numberOfOpenEdges.begin()+current_surface);
    updateThreshold(threshold);
    if(!whole)
        showComponentSurface();
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

    vtkSmartPointer<vtkPointPicker> pointPicker = vtkSmartPointer<vtkPointPicker>::New();


    ((VTKWindow*)window)->getWidget()->GetRenderWindow()->AddRenderer(renderer);
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(surface->GetOutputPort());
    mapper->ScalarVisibilityOff();

    vtkSmartPointer<vtkActor> actor_annotations = vtkSmartPointer<vtkActor>::New();
    actor_annotations->SetMapper(mapper);



    // Add the actor to the scene
     renderer->AddActor(actor_annotations);

    //actor.SetNumberOfCloudPoints( 1000000 );
    actor->SetMapper(mapper);
    //vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    //renderer->SetBackground(.1, .2, .3);

    renderer->AddActor(actor);

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
    cout << "Annotations : " << Annotations.size()<< endl;
    makeConnectedSurfaces();
    //surface->update();
    actor->VisibilityOff();

    cout << big << endl;
    cout << small << endl;

    celldata[0]->Allocate(celldata[0]->EstimateSize(big, 3));
    celldata[1]->Allocate(celldata[1]->EstimateSize(small, 3));

    cout << connectedComponents.size() << endl;
    //vtkIdType npts; vtkIdType *pts;
    for(int i=0; i<connectedComponents.size(); i++) {
        connectedComponents[i]->InitTraversal();
        if(connectedComponents[i]->GetNumberOfCells()>threshold) {
            while(connectedComponents[i]->GetNextCell(npts, pts))
                celldata[0]->InsertNextCell(npts, pts);
        }
        else {
            while(connectedComponents[i]->GetNextCell(npts, pts))
                celldata[1]->InsertNextCell(npts, pts);
        }
    }

    cout << "I print here" << endl;
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
    //actor1->VisibilityOff();
    renderer->AddActor(actor1);
    renderer->AddActor(actor2);

    cout << "After all this I still print : " << Annotations.size() << endl;
/*
    colors->SetNumberOfComponents(3);
    colors->SetName ("Colors");
    //colors->InsertNextTupleValue(red);
    //colors->InsertNextTupleValue(green);
    //colors->InsertNextTupleValue(blue);


    for(int i=0;i<Annotations.size();i++)
    {
        points->InsertNextPoint (Annotations[i].x, Annotations[i].y, Annotations[i].z);
        unsigned char color[3] = {Annotations[i].r, Annotations[i].g, Annotations[i].b};
        colors->InsertNextTupleValue(color);
    }
    pointsPolydata->SetPoints(points);
    vertexFilter->SetInputData(pointsPolydata);
    vertexFilter->Update();
    polydata->ShallowCopy(vertexFilter->GetOutput());
    polydata->GetPointData()->SetScalars(colors);

    mapper3->SetInputData(polydata);
    actor3->SetMapper(mapper3);
    actor3->GetProperty()->SetPointSize(10);
*/
    //vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    QVTKInteractor* iren = QVTKInteractor::New();
    renderer->GetRenderWindow()->SetInteractor(iren);
    iren->Initialize();
    vtkSmartPointer<MouseInteractorStyleDoubleClick> style = vtkSmartPointer<MouseInteractorStyleDoubleClick>::New();
    //renderWindowInteractor->SetInteractorStyle( style );

    vtkInteractorStyle* s = vtkInteractorStyleTrackballCamera::New();
    iren->SetInteractorStyle(style);
    iren->SetPicker(pointPicker);

/*
    renderer->AddActor(actor3);
  */
  //iren->setRenderWindow(renderer->GetRenderWindow());
    //renderWindowInteractor->SetPicker(pointPicker);
    //renderWindowInteractor->SetRenderWindow(renderer->GetRenderWindow());

    //vtkSmartPointer<MouseInteractorStylePP> style = vtkSmartPointer<MouseInteractorStylePP>::New();
    //renderWindowInteractor->SetInteractorStyle( style );
    //renderWindowInteractor->Start();
}



