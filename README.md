# MedicalVisualization

An interactive visualization and editing system for medical images/data(DICOM) that would also serve as a front-end for 3D printing medically precise objects which could be used in implants or surgery planning. Import and render medical voxel data. Extract iso-surfaces, run geometric algorithms to analyze the surface mesh and send tessellated data to the 3D printer. 

Additional Features :
* 3D Models of scans can be annotated, useful as a teching tool.
* Ability to distinguish between bone, tissue, muscle etc, based on pixel intensity in a scan, and generate surfaces of specific parts using iso-surface extraction.
* Find connected components, helps in cleaning up noise in the 3D reconstruction of the medical scans.

Drawbacks :
* Sometimes, a high resolution scan is required for all the features in the tool to work accurately.

Libraries and frameworks used : VTK, Qt
