classdef h5_file_h < handle
    %
    %   Class:
    %   adinstruments.h5_file_h
    
    properties
        file_path
        m %Handle to the file.
    end
    
    methods
        function obj = h5_file_h(file_path)
            %
            %    obj = adinstruments.h5_file_h(file_path)
            %
            %    See Also:
            %    adinstruments.readFile
            
            %TODO: Since we are not using this right away, we might
            %want to try and get the file path if it were evaluated
            %currently (in case it is relative)
            obj.file_path = file_path;
            obj.m = h5m.file.open(file_path);
            
            %Let's convert meta to structs here ...
            %--------------------------------------
            rr = @(attr)num2cell(h5readatt(file_path,'/record_meta',attr));

            record_struct = struct(...
                'n_ticks',rr('n_ticks'),...
                'tick_dt',rr('tick_dt'),...
                'record_start',rr('record_start'),...
                'data_start',rr('data_start'));

           %Comments
           rco = @(attr)num2cell(h5readatt(file_path,'/comments',attr)); 
           
           rs = @(attr,group_name)cellstr(char(h5readatt(file_path,group_name,attr))); 
           
%            temp = h5readatt(file_path,'/comments','str');
%            comment_strs = cellstr(char(temp));
           
           comment_struct = struct(...
               'str',rs('str','/comments'),...
               'id',rco('id'),...
               'tick_position',rco('tick_position'),...
               'channel',rco('channel'),...
               'tick_dt',rco('tick_dt'));
           
           %Channels
           %-----------------------------
           rch1  = @(attr)h5readatt(file_path,'/channel_meta',attr);
           rch2 = @(attr)num2cell(rch1(attr));
           
           id = rch2('id');
           n_rows = length(id);
           dt = mat2cell(rch1('dt'),1,2);
           n_samples = mat2cell(rch1('n_samples'),nrows,1);
           
           units_temp = cellstr(char(rch1('units')));
           
           n_records = length(record_struct);
           units_temp2 = reshape(units_temp,[n_rows n_records]);
           units
           
           %dt - separate by rows
           %n_samples - " "
           %units - yikes ... - by rows, but also char
           channel_struct = struct(...
            'name',rs('name','/channel_meta'),...
            'id',id,...
            'dt',dt,...
            'n_samples',n_samples);
        
           
           
           
           
           
        
        keyboard
  
% temp = vertcat(objs.units);
% temp = int16(char(temp(:)));
% h5writeatt(save_path,group_name,'units',temp);
% h5writeatt(save_path,group_name,'dt',vertcat(objs.dt));
% h5writeatt(save_path,group_name,'n_samples',vertcat(objs.n_samples));  
        end
        function delete(obj)
            %TODO: Delete
        end
    end
    
end

