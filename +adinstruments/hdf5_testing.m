%hdf5_testing

function hdf5_testing()


%       adinstruments.hdf5_testing

% % % file_path = 'C:\Data\GSK\ChrisRaw\140113 pelvic and hypogastric nerve recordings.mat';
% % % 
% % % 
% % %   %Example:  Append to an unlimited dataset.
% % %   

      N = 10000000;

      %Old version
    
      delete('myfile.h5')
      h5create('myfile.h5','/DS3',[N Inf],'ChunkSize',[N 1]);
      %h5disp('myfile.h5');
      tic
      for j = 1:10
           data = j*ones(N,1);
           start = [1 j];
           count = [N 1];
           h5write('myfile.h5','/DS3',data,start,count);
      end
      toc
      
      %Properties
      %================================
      %h5p.create(class_id)

      %Steps:
      %================
      %create object
      
      
      %{
       'H5P_ATTRIBUTE_CREATE' 
       'H5P_DATASET_ACCESS' 
       'H5P_DATASET_CREATE' 
       'H5P_DATASET_XFER' 
       'H5P_DATATYPE_CREATE' 
       'H5P_DATATYPE_ACCESS' 
       'H5P_FILE_MOUNT' 
       'H5P_FILE_CREATE' 
       'H5P_FILE_ACCESS' 
       'H5P_GROUP_CREATE' 
       'H5P_GROUP_ACCESS' 
       'H5P_LINK_CREATE' 
       'H5P_LINK_ACCESS' 
       'H5P_OBJECT_COPY' 
       'H5P_OBJECT_CREATE' 
       'H5P_STRING_CREATE' 
      
      
      %}
      
      %API REFERENCE
      %=============
      %http://www.hdfgroup.org/HDF5/doc/RM/RM_H5Front.html
      
      %STEP 1: File creation
      %---------------------
      %
      %H5F.create(name,flags,fcpl_id,fapl_id)
      %File creation property list  (fcpl_id): H5P_FILE_CREATE
      %     http://www.hdfgroup.org/HDF5/Tutor/property.html#cf
      %File access property list (fapl_id): H5P_FILE_ACCESS
      %     http://www.hdfgroup.org/HDF5/Tutor/property.html#fa
% %       file_id    = H5F.create(name,flags,'H5P_DEFAULT','H5P_DEFAULT');
% %       
% %       
% %       tic
% %       %(base_id,h5_dims)
% %       %NOTE: Dims are reversed from Matlab
% %       datatype_id = H5T.array_create(H5T.copy('H5T_NATIVE_DOUBLE'),[10 100000]);
% %       
% %       %http://www.hdfgroup.org/HDF5/doc/RM/RM_H5S.html#Dataspace-Create
% %       dataspace_id = H5S.create('H5S_SIMPLE');
      
  

%HDF5 ONLINE DOCUMENTATION
%==============================================
%Dataset Interfaces: http://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html
%Dataset Creation Properties: http://www.hdfgroup.org/HDF5/doc/RM/RM_H5P.html#DatasetCreatePropFuncs
%
%Dataspace Interfaces: http://www.hdfgroup.org/HDF5/doc/RM/RM_H5S.html
%
%Datatype Interfaces: http://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html

%


      
      %(loc_id, name, type_id, space_id, lcpl_id, dcpl_id, dapl_id)
      %loc_id   - file or group identifier
      %name     - name of the dataset
      %type_id  - datatype identifier
      %space_id - dataspace identifier
      %
      %PROPERTIES
      %lcpl_id  - Link creation property list - H5P_LINK_CREATE
      %
      %    governs creation of the link(s) by which the new dataset is 
      %    accessed and the creation of any intermediate groups that may 
      %    be missing.
      %
      %dcpl_id  - Dataset creation property list - H5P_DATASET_CREATE
      %
      %
      %dapl_id  - Dataset access property list - H5P_DATASET_ACCESS
      %
      
      
      delete('wtf.h5')
      file_id    = H5F.create('wtf.h5','H5F_ACC_EXCL','H5P_DEFAULT','H5P_DEFAULT');
      
      tic
      
      %Why allow array creation, what does this do????
      %datatype_id  = H5T.array_create(H5T.copy('H5T_NATIVE_DOUBLE'),[10 N]);
      
      type_id = H5T.copy('H5T_NATIVE_DOUBLE');
      
      %NOTE: Make sure to 
      dataspace_id = H5S.create_simple(2, [N 10], [N 10]);
      
      dcpl_id = H5P.create('H5P_DATASET_CREATE');
      %H5P.set_alloc_time(dcpl_id,'H5D_ALLOC_TIME_EARLY');
      %H5P.set_fill_time(dcpl_id,'H5D_FILL_TIME_NEVER');
      %H5P.set_layout(dcpl_id,'H5D_CHUNKED')
      %H5P.set_chunk(dcpl_id,[1 1])
      
      dataset_id = H5D.create(file_id,'DS3',type_id,dataspace_id,'H5P_DEFAULT',dcpl_id,'H5P_DEFAULT');


      N_2 = N;
      mem_space_id = H5S.create_simple(2,[N_2 1],[]);
      for j = 1:10
           data  = j*ones(1,N_2);
           start = [0 j-1]; %0 based indexing
           count = [N_2 1];
           
           H5S.select_hyperslab(dataspace_id,'H5S_SELECT_SET',start, [],[],count);
           %H5D.write(dataset_id, 'H5ML_DEFAULT', mem_space_id, dataspace_id, 'H5P_DEFAULT', data)
           H5D.write(dataset_id, 'H5ML_DEFAULT', mem_space_id, dataspace_id, 'H5P_DEFAULT', data)
           
      end
      toc

      H5D.close(dataset_id)
      H5F.close(file_id)
      
      
      
% % % %       H5P.close(dcpl_id)
% % % %       H5S.close(dataspace_id)
% % % %       H5T.close(datatype_id)
% % % %       
% % % %       
% % % %         srcFile = fullfile(matlabroot,'toolbox','matlab','demos','example.h5');
% % % %         copyfile(srcFile,'myfile.h5');
% % % %         fileattrib('myfile.h5','+w');
% % % %         plist = 'H5P_DEFAULT';
% % % %         fid = H5F.open('myfile.h5','H5F_ACC_RDWR',plist);
% % % %         dset_id = H5D.open(fid,'/g4/world');
% % % %         
% % % %         block = [10 5];
% % % %         h5_block = fliplr(block);
% % % %         mem_space_id = H5S.create_simple(2,h5_block,[]);
% % % %         
% % % %         
% % % %         file_space_id = H5D.get_space(dset_id);
% % % %         start = [15 5];
% % % %         h5_start = fliplr(start);
% % % %         H5S.select_hyperslab(file_space_id,'H5S_SELECT_SET',h5_start,[],[],h5_block);
% % % %         
% % % %         
% % % %         data = rand(block);
% % % %         H5D.write(dset_id,'H5ML_DEFAULT',mem_space_id,file_space_id,plist,data);
% % % %         H5D.close(dset_id);
% % % %         H5F.close(fid);
      
      

        
        
        
      
                 %(dataset_id, mem_type_id, mem_space_id, file_space_id, plist_id,buf)
           %mem_type_id   - see types - ??? Is this what is being passed in?
           %        H5ML_DEFAULT - let Matlab decide - might be quicker to
           %        not and instead use datatype_id from above
           %mem_space_id  - specified for getting from data, can be H5S_ALL
           %file_space_id - specified for writing from file, can be H5S_ALL
           %plist_id
           %buf
           
           %http://www.hdfgroup.org/HDF5/doc/RM/RM_H5S.html#Dataspace-SelectHyperslab
           %
           %(space_id,operation,h5_start, h5_stride, h5_count, h5_block)
      
      
      
      
      %file => group or dataset => 
   
      %{
Library (H5)
    General-purpose functions for use with entire HDF5 library, such as initialization
Attribute (H5A)
    Metadata associated with datasets or groups
Dataset (H5D)
    Multidimensional arrays of data elements and supporting metadata
Dimension Scale (H5DS)
    Dimension scale associated with dataset dimensions
Error (H5E)
    Error handling
File (H5F)
    HDF5 file access
Group (H5G)
    Organization of objects in file
Identifier (H5I)
    HDF5 object identifiers
Link (H5L)
    Links in file
MATLAB (H5ML)
    MATLAB Utility functions not part of HDF5 library
Object (H5O)
    Objects in file
Property (H5P)
    Object property lists
Reference (H5R)
    HDF5 references
Dataspace (H5S)
    Dimensionality of dataset
Datatype (H5T)
    Type of variable stored in dataset
Filters and Compression (H5Z)
    Inline data filters, data compression
      %}
      %h5g - group interface
      
      %{
      To create an empty dataset (no data written) the following steps need to be taken:

1. Obtain the location identifier where the dataset is to be created.
2. Define or specify the dataset characteristics:
    a. Define a datatype or specify a pre-defined datatype.
    b. Define a dataspace.
    c. Specify the property list(s) or use the default.
3. Create the dataset.
4. Close the datatype, the dataspace, and the property list(s) if necessary.
5. Close the dataset.
      
%}
        