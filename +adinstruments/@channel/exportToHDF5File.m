function exportToHDF5File(objs,fobj,save_path)

DEFLATE_VALUE = 3;
MAX_SAMPLES_AT_ONCE = 1e8; %TODO: Get from options

group_name = '/channel_meta';
h5m.group.create(fobj,'channel_version');
h5writeatt(save_path,'/channel_version','version',1);

h5m.group.create(fobj,group_name);
%TODO: Rewrite with h5m library

h5writeatt(save_path,group_name,'name',int16(char({objs.name})));
h5writeatt(save_path,group_name,'id',[objs.id]);

temp = vertcat(objs.units);
temp = int16(char(temp(:)));
h5writeatt(save_path,group_name,'units',temp);
h5writeatt(save_path,group_name,'dt',vertcat(objs.dt));
h5writeatt(save_path,group_name,'n_samples',vertcat(objs.n_samples));

h5m.group.create(fobj,'data_version');
h5writeatt(save_path,'/data_version','version',1);

%Now onto saving the data
%----------------------------------------------
n_objs    = length(objs);
n_records = objs(1).n_records;
for iChan = 1:n_objs
    cur_chan = objs(iChan);
    for iRecord = 1:n_records
        cur_n_samples = cur_chan.n_samples(iRecord);
        chan_name     = sprintf('/data__chan_%d_rec_%d',iChan,iRecord);
        
        h5create(save_path,chan_name,[cur_n_samples 1],'ChunkSize',...
            [min(MAX_SAMPLES_AT_ONCE,cur_n_samples) 1],'Datatype','single',...
            'Deflate',DEFLATE_VALUE);
        
        
        if cur_n_samples < MAX_SAMPLES_AT_ONCE
            %This is a write sequence
            
            h5write(save_path, chan_name, ...
                cur_chan.getAllData(iRecord,'leave_raw',true));
        else
            
            start_I = 1:MAX_SAMPLES_AT_ONCE:cur_n_samples;
            end_I   = MAX_SAMPLES_AT_ONCE:MAX_SAMPLES_AT_ONCE:cur_n_samples;
            
            if length(end_I) < length(start_I)
                end_I(end+1) = cur_n_samples; %#ok<AGROW>
            end
            
            for iChunk = 1:length(start_I)
                cur_start = start_I(iChunk);
                cur_end   = end_I(iChunk);
                n_samples_get = cur_end-cur_start + 1;
                
                data = cur_chan.getDataSubset(iRecord,cur_start,n_samples_get,'leave_raw',true);
                h5write(save_path,chan_name,data,[cur_start 1],[length(data) 1],[1 1])
            end
        end
    end
end


end