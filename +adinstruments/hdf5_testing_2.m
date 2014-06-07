%hdf5_testing

function hdf5_testing_2()
%
%
%   From original testing. If you must write columns of data (or rows?)
%   then chunking will help with write speed since it makes the data
%   continuous on file where as if in a matrix it would not be.
%
%
%   Now what about parts of a large vector??????
%
%   NOTE: 


%       adinstruments.hdf5_testing_2

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
      
      delete('wtf.h5')
      file_id    = H5F.create('wtf.h5','H5F_ACC_EXCL','H5P_DEFAULT','H5P_DEFAULT');
      
      tic
      
      %Why allow array creation, what does this do????
      %datatype_id  = H5T.array_create(H5T.copy('H5T_NATIVE_DOUBLE'),[10 N]);
      
      type_id = H5T.copy('H5T_NATIVE_DOUBLE');
      
      %NOTE: Make sure to 
      dataspace_id = H5S.create_simple(2, [N 10], [N 10]);
      
      dcpl_id = H5P.create('H5P_DATASET_CREATE');
      H5P.set_alloc_time(dcpl_id,'H5D_ALLOC_TIME_EARLY');
      H5P.set_fill_time(dcpl_id,'H5D_FILL_TIME_NEVER');
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
           
           H5D.write(dataset_id, 'H5ML_DEFAULT', mem_space_id, dataspace_id, 'H5P_DEFAULT', data)
           
      end
      toc

      H5D.close(dataset_id)
      H5F.close(file_id)
        