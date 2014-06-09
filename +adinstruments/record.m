classdef (Hidden) record < sl.obj.display_class
    %
    %   Class:
    %   adinstruments.record
    %
    %   A new record is created in a file whenever settings are changed, or
    %   whenever the users stops (then starts) a recording.
    
    properties
        id        %record number (1 based)
        n_ticks   %# of samples of highest sampling rate channel
        comments  %adinstruments.comment
        tick_dt   %The highest sampling rate of any channel in this record.
        tick_fs   %Sampling frequency, computed for convenience from tick_dt
        record_start %(Matlab time)
        
        data_start  %(Matlab time) Time at which the data that was collected 
        %during the record was collected. This may not correspond to the
        %record_start if a trigger delay was involved.
        
        data_start_str
    end
    
    properties (Hidden)
       file_h %adinstruments.file_handle
    end
    
    methods
        function obj = record(file_h,sdk,record_id)
           %
           %
           %
           
           obj.file_h = file_h;
           obj.id     = record_id;
                      
           obj.n_ticks  = sdk.getNTicksInRecord(file_h,record_id);
           
           [obj.record_start,obj.data_start] = sdk.getRecordStartTime(file_h,record_id);

           obj.data_start_str = datestr(obj.data_start);
           
           %This is not channel specific, the channel input is not actually
           %used:
           %http://forum.adinstruments.com/viewtopic.php?f=7&t=563
           obj.tick_dt  = sdk.getTickPeriod(file_h,record_id,1);
           obj.tick_fs  = 1./obj.tick_dt;
           
           obj.comments = sdk.getAllCommentsForRecord(file_h,obj.id,obj.tick_dt);
        end
        function exportToHDF5File(objs,fobj,save_path)
           group_name = '/record_meta';
           h5m.group.create(fobj,'record_version');
           h5writeatt(save_path,'/record_version','version',1);
           
           h5m.group.create(fobj,group_name);
           %TODO: Rewrite with h5m library
           h5writeatt(save_path,group_name,'n_ticks',[objs.n_ticks]);
           h5writeatt(save_path,group_name,'tick_dt',[objs.tick_dt]);
           h5writeatt(save_path,group_name,'record_start',[objs.record_start]);
           h5writeatt(save_path,group_name,'data_start',[objs.data_start]);
           
           %exportToHDF5File([objs.comments],fobj,save_path)
        end
        function exportToMatFile(objs,m)
            
           m.record_version = 1; 
           m.record_meta = struct(...
               'n_ticks',       {objs.n_ticks}, ...
               'tick_dt',       {objs.tick_dt},...
               'record_start',  {objs.record_start},...
               'data_start',    {objs.data_start});
               
           exportToMatFile([objs.comments],m)
        end
    end
    
end

