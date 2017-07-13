#include <QColorDialog>
#include <QInputDialog>
#include <vtkSTLWriter.h>
#include <vtkSTLReader.h>
#include <vtkCleanPolyData.h>
#include <vtkAppendPolyData.h>
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
#include <vtkPropPicker.h>
#include <vtkCellLocator.h>
#include "vtksurface.h"
#include "window.h"
#include "vtkwindow.h"

vector<Annotation> Annotations;

// Define interaction style
class MouseInteractorStylePP : public vtkInteractorStyleTrackballCamera
{
  public:
    static MouseInteractorStylePP* New();
    vtkTypeMacro(MouseInteractorStylePP, vtkInteractorStyleTrackballCamera);
    int yTextPos = 700;
    bool pick = false;
    bool annotate = false;
    VTKSurface* surface;
    virtual void OnLeftButtonDown()
    {
        if(pick) {
            std::cout << "Picking pixel: " << this->Interactor->GetEventPosition()[0] << " " << this->Interactor->GetEventPosition()[1] << std::endl;
            // Pick from this location.
            vtkSmartPointer<vtkPropPicker>  picker = vtkSmartPointer<vtkPropPicker>::New();
            picker->Pick(this->Interactor->GetEventPosition()[0],
                             this->Interactor->GetEventPosition()[1],
                             0,  // always zero.
                             this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
            double picked[3];
            picker->GetPickPosition(picked);
            std::cout << "Picked value: " << picked[0] << " " << picked[1] << " " << picked[2] << std::endl;
            vtkSmartPointer<vtkActor> actor = picker->GetActor();
            if(annotate && actor) {
                vector<vtkSmartPointer<vtkActor> > act = surface->getActors();
                for(int i=0; i<act.size(); i++) {
                    if(actor==act[i]) {
                        Annotation a;
                        a.x = picked[0] ;
                        a.y = picked[1] ;
                        a.z = picked[2] ;
                        //QColor colour = QColorDialog::getColor();
                        a.r = 1.0;
                        a.g = 1.0;
                        a.b = 1.0;
                        vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
                        sphereSource->SetCenter(a.x, a.y , a.z);
                        sphereSource->SetRadius(5.0);
                        vtkSmartPointer<vtkPolyDataMapper> mapper4 = vtkSmartPointer<vtkPolyDataMapper>::New();
                        vtkSmartPointer<vtkActor> actor4 = vtkSmartPointer<vtkActor>::New();
                        mapper4->SetInputConnection(sphereSource->GetOutputPort());
                        actor4->SetMapper(mapper4);
                        actor4->GetProperty()->SetColor(a.r, a.g, a.b);
                        this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(actor4);
                        QColor colour = QColorDialog::getColor();
                        a.r = colour.red()/255.0;
                        a.g = colour.green()/255.0;
                        a.b = colour.blue()/255.0;
                        actor4->GetProperty()->SetColor(a.r, a.g, a.b);
                        // Setup the text and add it to the renderer
                        QString str = QInputDialog::getText(0, "Annotation Text", "Enter Text:");
                        a.text = str.toStdString();
                        vtkSmartPointer<vtkTextActor> textActor = vtkSmartPointer<vtkTextActor>::New();
                        textActor->SetInput (a.text.c_str());
                        textActor->SetPosition ( 10, yTextPos );
                        textActor->GetTextProperty()->SetFontSize ( 16 );
                        textActor->GetTextProperty()->SetColor (a.r, a.g, a.b);
                        a.actor = actor4;
                        a.surfaceActor = act[i];
                        a.textActor = textActor;
                        a.index = i;
                        Annotations.push_back(a);
                        this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor2D (textActor);
                        yTextPos = yTextPos - 20;
                    }
                }
                annotate=false;
            }
            else {
                vtkSmartPointer<vtkActor> actor = picker->GetActor();
                if(actor) {
                    vector<vtkSmartPointer<vtkActor> > a = surface->getActors();
                    for(int i=0; i<a.size(); i++) {
                        if(actor==a[i]) {
                            if(actor->GetProperty()->GetColor()[0]==0.0 && actor->GetProperty()->GetColor()[1]==0.0 && actor->GetProperty()->GetColor()[2]==1.0) {
                                actor->GetProperty()->SetColor(1.0, 1.0, 1.0);
                                cout << "Unpicking" << endl;
                            }
                            else {
                                actor->GetProperty()->SetColor(0.0, 0.0, 1.0);
                                cout << "Picking" << endl;
                            }
                        }
                    }
                }
            }
            this->Interactor->GetRenderWindow()->Render();
            // Forward events
            //vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
        }
        else {
            vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
        }
    }
    void setPick(bool p) {
        pick = p;
    }
    void setAnnotate(bool a) {
        annotate = a;
    }
    void setVTKSurface(VTKSurface* s) {
        surface = s;
    }
};

vtkStandardNewMacro(MouseInteractorStylePP);

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
    data2 = vtkSmartPointer<vtkPolyData>::New();
    celldata2 = vtkSmartPointer<vtkCellArray>::New();
    small=0;
    big=0;
    actor = vtkSmartPointer<vtkActor>::New();
    actor2 = vtkSmartPointer<vtkActor>::New();
    mapper2 = vtkSmartPointer<vtkPolyDataMapper>::New();
    pick = false;
    style = vtkSmartPointer<MouseInteractorStylePP>::New();
}

double VTKSurface::getIsovalueStart() {
    return isovalue_start;
}

double VTKSurface::getIsovalueEnd() {
    return isovalue_end;
}

void VTKSurface::setIsovalueStart(double val) {
    isovalue_start = val;
}

void VTKSurface::setIsovalueEnd(double val) {
    isovalue_end = val;
}

vector < vector<double> > VTKSurface::getPtsOnSlice()
{
    return points_on_slice;
}

void VTKSurface::setPtsOnSlice(vector < vector<double> > pts)
{
    points_on_slice = pts;
}

vector<vtkSmartPointer<vtkActor> > VTKSurface::getActors() {
    return allActors;
}

void VTKSurface::setLayers(Layer* layers, int n) {
    this->layers = layers;
    numberOfLayers = n;
}

void VTKSurface::setImageData(ImageData* data) {
    imageData = (VTKImageData*) data;
    imageData->getImageData()->GetExtent(extent);
    imageData->getImageData()->GetBounds(bounds);
}


vector<double> VTKSurface::returnClosestPoint(double x, double y, double z)
{
    // Create the tree
      vtkSmartPointer<vtkCellLocator> cellLocator =
        vtkSmartPointer<vtkCellLocator>::New();
      //change this
      cellLocator->SetDataSet(imageData->getImageData());
      cellLocator->BuildLocator();

      double testPoint[3] = {x,y,z};

      //Find the closest points to TestPoint
      double closestPoint[3];//the coordinates of the closest point will be returned here
      double closestPointDist2; //the squared distance to the closest point will be returned here
      vtkIdType cellId; //the cell id of the cell containing the closest point will be returned here
      int subId; //this is rarely used (in triangle strips only, I believe)
      cellLocator->FindClosestPoint(testPoint, closestPoint, cellId, subId, closestPointDist2);

        cout << "actual point : " << x << ", " << y << ", " << z << endl;
      std::cout << "Coordinates of closest point: " << closestPoint[0] << " " << closestPoint[1] << " " << closestPoint[2] << std::endl;
      std::cout << "Squared distance to closest point: " << closestPointDist2 << std::endl;
      std::cout << "CellId: " << cellId << std::endl;
      vector < double> closestPt;
      closestPt.push_back(closestPoint[0]);
      closestPt.push_back(closestPoint[1]);
      closestPt.push_back(closestPoint[2]);
      return closestPt;
}

// creating the modified 0-1 data and generating the surface
void VTKSurface::createSurface()
{
    modifiedData->DeepCopy(imageData->getImageData());
    for(int x=extent[0];x<=extent[1];x++) {
        for(int y=extent[2];y<=extent[3];y++) {
            for(int z=extent[4];z<=extent[5];z++) {
                //double* pixel =  static_cast<double*>(data->GetOutput()->GetScalarComponentAsFloat(x,y,z,1));
                //float* pixel1 = static_cast<float*>(modifiedData->GetScalarPointer(x,y,z));
                float pixel2 =  (imageData->getImageData()->GetScalarComponentAsFloat(x,y,z,0));
               // vtkIdType id = returnCellId(x,y,z);
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

}

/*void VTKSurface::copyData()
{

}
*/
bool visited[700][700][700];

//for given set of cell id's travel their connected cells and put 1 and 0
void VTKSurface::createSurface1()
{
    //cout << this->isovalue_start << ", " << this->isovalue_end << endl;
    //for all points in the chosen points array ..
      //      recur
    for(int i=0;i<700;i++)
    {
        for(int j=0;j<700;j++)
        {
            for(int k=0;k<700;k++)
            {
                visited[i][j][k] = false;
            }
        }
    }
    modifiedData->DeepCopy(imageData->getImageData());
    for(int x=extent[0];x<=extent[1];x++) {
        for(int y=extent[2];y<=extent[3];y++) {
            for(int z=extent[4];z<=extent[5];z++) {
                float pixel2 =  (imageData->getImageData()->GetScalarComponentAsFloat(x,y,z,0));
                modifiedData->SetScalarComponentFromFloat(x,y,z,0,0.0);
            }
        }
    }

        int ptx = points_on_slice[0][0]; int pty = points_on_slice[0][1]; int ptz = points_on_slice[0][2];
    cout << ptx << ", " << pty << ", " << ptz << endl;
    //vector< double> point_on_volume = returnClosestPoint(ptx, pty, ptz);
    recur(ptx, pty, ptz);
    surface->ComputeNormalsOn();
    surface->GenerateTrianglesOn();
    surface->SetInputData(modifiedData);
    surface->SetValue(0, 0.5);
}

//pass the closest point
void VTKSurface::recur(double x, double y, double z)
{
    //cout << "extent : " << extent[0] << " .." << extent[2] << ".. " << extent[4] << endl;
    x = int(x); y = int(y); z = int(z);
    if (visited[int(x)][int(y)][int(z)] == false  && x>extent[0] && x<extent[1] && y>extent[2] && y<extent[3] && z>extent[4] && z<extent[5])
        {
        float pixel2 =  (imageData->getImageData()->GetScalarComponentAsFloat(x,y,z,0));
        visited[int(x)][int(y)][int(z)] = true;
        //cout << "before "  << x << " - " << y  << " - " << z<< endl;
        //cout << "after" << endl;
         if(x>extent[0] && x<extent[1] && y>extent[2] && y<extent[3] && z>extent[4] && z<extent[5]) {
                if(pixel2>= isovalue_start && pixel2<= isovalue_end) {
                    //cout << "in " << endl;
                    modifiedData->SetScalarComponentFromFloat(x,y,z,0,1.0);
                    recur(x+1,y,z);
                    if(x-1 >= 0)
                        {
                        //recur(x-1, y, z);
                        }
                    recur(x, y+1, z);
                    recur(x,y, z+1);
                    cout << x << endl;

                    if(y-1 >=0)
                        {
                        recur(x, y-1, z);
                        }
                    if(z-1>=0)
                        {
                            recur(x,y,z-1);
                        }
                    }
                else
                    {
                    return;
                    }
            }
        else
            {
                return;
            }
    }
    else
    {
        return;
    }

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
        // getting all cells (triangles) of that point all_connected_cells[i]
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
            // Point i visited
            Array[i] = true;
            //call recursion on every pointID in connectedCells
            subsurfaces.clear();
            long c = findConnectedVertsRecur(i);
            createConnectedSurfaces();
        }
    }
    sort(connectedComponents.begin(), connectedComponents.end(), compareFunc());

    // checking number of open edges to check if the surface is closed
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
    actor2->GetProperty()->SetOpacity(1.0);
    for(int i=0; i<actor1.size(); i++) {
        actor1[i]->GetProperty()->SetOpacity(1.0);
        actor1[i]->GetProperty()->SetColor(red, blue, green);
    }
    actor2->GetProperty()->SetColor(1.0, 0.0, 0.0);
    actor->VisibilityOff();
    renderer->GetRenderWindow()->Render();
}

void VTKSurface::showComponentSurface() {
    whole = false;
    if(current_surface>=connectedComponents.size())
        current_surface=connectedComponents.size()-1;
    surfacePolygons->SetPolys(connectedComponents[current_surface]);
    surface->Update();
    if(surface->GetOutput()->GetPolys()->GetNumberOfCells()>threshold)
        actor->GetProperty()->SetColor(red, blue, green);
    else
        actor->GetProperty()->SetColor(1.0, 0.0, 0.0);
    actor2->GetProperty()->SetOpacity(0.1);
    for(int i=0; i<actor1.size(); i++) {
        actor1[i]->GetProperty()->SetOpacity(0.1);
        actor1[i]->GetProperty()->SetColor(red, blue, green);
    }
    actor2->GetProperty()->SetColor(1.0, 0.0, 0.0);
    actor->VisibilityOn();
    if(!visible[current_surface])
        actor->VisibilityOff();
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

// Get minimum number of triangles in all connected components
long VTKSurface::getMinimum() {
    long mini = 10000000;
    for(int i=0; i<connectedComponents.size(); i++) {
        if(connectedComponents[i]->GetNumberOfCells()<mini)
            mini=connectedComponents[i]->GetNumberOfCells();
    }
    return mini;
}

// Get maximum number of triangles in all connected components
long VTKSurface::getMaximum() {
    long maxi = 0;
    for(int i=0; i<connectedComponents.size(); i++) {
        if(connectedComponents[i]->GetNumberOfCells()>maxi)
            maxi=connectedComponents[i]->GetNumberOfCells();
    }
    return maxi;
}

// updates all the actors according to the threshold
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

    cout << "small :" << small << endl;

    for(int i=0; i<actor1.size(); i++)
        renderer->RemoveActor(actor1[i]);

    celldata2->Reset();
    celldata2 = vtkSmartPointer<vtkCellArray>::New();
    celldata2->Allocate(celldata2->EstimateSize(small+1, 3));
    actor1.clear();

    cout << connectedComponents.size() << endl;
    //vtkIdType npts; vtkIdType *pts;
    for(int i=0; i<connectedComponents.size(); i++) {
        if(connectedComponents[i]->GetNumberOfCells()>threshold) {
            if(visible[i]) {
                vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
                polydata->ShallowCopy(wholeSurfacePolygons);
                polydata->SetPolys(connectedComponents[i]);
                vtkSmartPointer<vtkPolyDataMapper> map = vtkSmartPointer<vtkPolyDataMapper>::New();
                map->SetInputData(polydata);
                map->ScalarVisibilityOff();
                allActors[i]->SetMapper(map);
                allActors[i]->GetProperty()->SetColor(red, blue, green);
                allActors[i]->GetProperty()->SetOpacity(1.0);
                actor1.push_back(allActors[i]);
                renderer->AddActor(allActors[i]);
            }
        }
        else {
            while(connectedComponents[i]->GetNextCell(npts, pts))
                if(visible[i]) {
                    celldata2->InsertNextCell(npts, pts);
                }
        }
    }
    vtkIdType temppts[] = {0,0,0};
    celldata2->InsertNextCell(3, temppts);
    data2->SetPolys(celldata2);
    renderer->GetRenderWindow()->Render();
}

// removing all surfaces which are below threshold
void VTKSurface::removeSurfaces() {
    int i=0;
    while(i<connectedComponents.size() && connectedComponents[i]->GetNumberOfCells()>threshold)
        i++;
    //connectedComponents.erase (connectedComponents.begin()+i,connectedComponents.end());
    //numberOfOpenEdges.erase (numberOfOpenEdges.begin()+i,numberOfOpenEdges.end());
    for(; i<visible.size(); i++)
        visible[i]=false;
    updateThreshold(threshold);
}

// removing a particular connected component surface
void VTKSurface::removeSurface() {
    //connectedComponents.erase (connectedComponents.begin()+current_surface);
    //numberOfOpenEdges.erase (numberOfOpenEdges.begin()+current_surface);
    visible[current_surface]=false;
    updateThreshold(threshold);
    for(int i=Annotations.size()-1; i>=0; i--) {
        if(Annotations[i].index == current_surface) {
            renderer->RemoveActor(Annotations[i].actor);
            renderer->RemoveActor2D(Annotations[i].textActor);
            Annotations.erase(Annotations.begin()+i);
        }
    }
    if(!whole)
        showComponentSurface();
}

// getting the number of triangles for the current surface
long VTKSurface::getNumberOfTriangles(bool status) {
    if(status)
        return polyArray->GetNumberOfCells();
    else
        return connectedComponents[current_surface]->GetNumberOfCells();
}

// create the connected surface from the temporary subsurfaces vector and appending it to connectedComponents
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

// Pick mode vs edit mode
void VTKSurface::changeMode(int mode) {
    if(mode==0)
        pick=false;
    else
        pick=true;
    style->setPick(pick);
}

// shift to annotation mode
void VTKSurface::addAnnotation() {
    style->setAnnotate(true);
}

void VTKSurface::render(Window *window)
{

    ((VTKWindow*)window)->getWidget()->GetRenderWindow()->AddRenderer(renderer);
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(surface->GetOutputPort());
    mapper->ScalarVisibilityOff();

    actor->SetMapper(mapper);
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

    celldata2->Allocate(celldata2->EstimateSize(small, 3));

    cout << connectedComponents.size() << endl;
    //vtkIdType npts; vtkIdType *pts;
    for(int i=0; i<connectedComponents.size(); i++) {
        allActors.push_back(vtkSmartPointer<vtkActor>::New());
        visible.push_back(true);
        connectedComponents[i]->InitTraversal();
        // add all major component actors to actor1 vector
        if(connectedComponents[i]->GetNumberOfCells()>threshold) {
            vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
            polydata->ShallowCopy(wholeSurfacePolygons);
            polydata->SetPolys(connectedComponents[i]);
            vtkSmartPointer<vtkPolyDataMapper> map = vtkSmartPointer<vtkPolyDataMapper>::New();
            map->SetInputData(polydata);
            map->ScalarVisibilityOff();
            allActors[i]->SetMapper(map);
            allActors[i]->GetProperty()->SetColor(red, blue, green);
            allActors[i]->GetProperty()->SetOpacity(1.0);
            actor1.push_back(allActors[i]);
            renderer->AddActor(allActors[i]);
        }
        // concatenate all minor component to celldata2
        else {
            while(connectedComponents[i]->GetNextCell(npts, pts))
                celldata2->InsertNextCell(npts, pts);
        }
    }

    data2->DeepCopy(wholeSurfacePolygons);
    data2->SetPolys(celldata2);
    mapper2->SetInputData(data2);
    mapper2->ScalarVisibilityOff();
    actor2->SetMapper(mapper2);
    actor2->GetProperty()->SetColor(1.0, 0.0, 0.0);
    actor2->GetProperty()->SetOpacity(1.0);
    renderer->AddActor(actor2);

    //vtkSmartPointer<vtkPointPicker> pointPicker = vtkSmartPointer<vtkPointPicker>::New();
    // interactor to pick points
    QVTKInteractor* iren = QVTKInteractor::New();
    style->SetDefaultRenderer(renderer);
    renderer->GetRenderWindow()->SetInteractor(iren);
    iren->SetRenderWindow(renderer->GetRenderWindow());
    iren->Initialize();
    iren->SetInteractorStyle(style);
    style->setVTKSurface(this);
    //iren->SetPicker(pointPicker);
}

void VTKSurface::setSpacing(vector<double> spacing)
{
    spacing_x = spacing[0]; spacing_y = spacing[1]; spacing_z = spacing[2];
}

// to write out all the picked components to an stl file
void VTKSurface::print() {
    vtkSmartPointer<vtkAppendPolyData> appendFilter = vtkSmartPointer<vtkAppendPolyData>::New();
    for(int i=0; i<actor1.size(); i++) {
        if(actor1[i]->GetProperty()->GetColor()[0]==0.0 && actor1[i]->GetProperty()->GetColor()[1]==0.0 && actor1[i]->GetProperty()->GetColor()[2]==1.0) {
            vtkPolyDataMapper* mapper = (vtkPolyDataMapper*) actor1[i]->GetMapper();
            vtkPolyData* data = mapper->GetInput();
            cout << "Printing Actor " << i << endl;
            appendFilter->AddInputData(data);
        }

    }
    appendFilter->Update();
    // Remove any duplicate points.
    vtkSmartPointer<vtkCleanPolyData> cleanFilter = vtkSmartPointer<vtkCleanPolyData>::New();
    cleanFilter->SetInputConnection(appendFilter->GetOutputPort());
    cleanFilter->Update();
    // write data to stl format
    QString str = QInputDialog::getText(0, "Enter filename", "Example : filename.stl:");
    std::string filename = str.toStdString();
    vtkSmartPointer<vtkSTLWriter> stlWriter = vtkSmartPointer<vtkSTLWriter>::New();
    stlWriter->SetFileName(filename.c_str());
    stlWriter->SetInputConnection(cleanFilter->GetOutputPort());
    stlWriter->Write();
}

