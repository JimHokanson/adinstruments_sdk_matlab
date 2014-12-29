classdef (Hidden) channel_writer < handle
    %
    %   Class:
    %   adi.channel_writer
    %
    %   This is meant to be an interface
    %
    %   adi.setChannelName(file_h,channel,channel_name)
    %   adi.sdk.setChannelInfo
    %   adi.sdk.addChannelSamples
    
    
    properties
        id
    end
    %NOTE: These are currently not write safe - they don't get updated
    properties
        name
        fs
        units
        enabled = true
    end
    
    properties (Hidden)
        parent %adi.file_writer
    end
    
    methods
        function obj = channel_writer(file_writer_obj,id,name,fs,units)
            %
            %
            %    adi.channel_writer(file_writer_obj,id,name,fs,units)
            
            obj.parent = file_writer_obj;
            obj.id = id;
            obj.name = name;
            obj.fs = fs;
            obj.units = units;
            
            obj.updateName();
            obj.updateInfo();
        end
        function updateName(obj)
            file_h = obj.parent.file_h;
            adi.sdk.setChannelName(file_h,obj.id,obj.name);
        end
        function updateInfo(obj)
            writer_h = obj.parent.data_writer_h;
            adi.sdk.setChannelInfo(writer_h,obj.id,1/obj.fs,obj.units,'enabled_for_record',obj.enabled);
        end
        function addSamples(obj,data)
            writer_h = obj.parent.data_writer_h;
            adi.sdk.addChannelSamples(writer_h,obj.id,data)
        end
    end
    
end

