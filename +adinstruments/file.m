classdef (Hidden) file < sl.obj.display_class
    %
    %   Class:
    %   adinstruments.file
    
    properties
        file_path
    end
    
    properties
        n_records
        n_channels
        records       %adinstruments.record
        channel_specs %adinstruments.channel
    end
    
    properties (Dependent)
        channel_names
    end
    
    methods
        function value = get.channel_names(obj)
            temp = obj.channel_specs;
            if isempty(temp)
                value = {};
            else
                value = {temp.name};
            end
        end
    end
    
    methods
        function obj = file(file_path,file_h,in)
            %
            %    This should be created by adinstruments.readFile.
            %
            %    See Also:
            %    adinstruments.readFile
            
            obj.file_path   = file_path;
            
            obj.n_records  = adinstruments.sdk.getNumberOfRecords(file_h);
            obj.n_channels = adinstruments.sdk.getNumberOfChannels(file_h);
            
            %Get record objects
            %-------------------------------------------
            temp = cell(1,obj.n_records);
            
            for iRec = 1:obj.n_records
                temp{iRec} = adinstruments.record(iRec,file_h);
            end
            
            obj.records = [temp{:}];
            
            %Get channel objects
            %-------------------------------------------
            temp = cell(1,obj.n_channels);
            
            for iChan = 1:obj.n_channels
                temp{iChan} = adinstruments.channel(file_h,iChan,obj.records);
            end
            
            obj.channel_specs = [temp{:}];
            
            if in.remove_empty_channels
               obj.channel_specs = obj.channel_specs.removeEmptyObjects(); 
            end
        end
        function summarizeRecords(obj)
            %For each record:
            %# of comments
            %which channels contain data
            %duration of the record
        end
        function chan = getChannelByName(obj,name,varargin)
            %
            %
            %   chan = ad_sdk.adinstruments.getChannelByName(obj,name,varargin)
            %
            %   See Also:
            %   adinstruments.channel.getChannelByName()
            
            in.case_sensitive = false;
            in.partial_match  = true;
            in = sl.in.processVarargin(in,varargin);
            
            temp = obj.channel_specs;
            if isempty(temp)
            	error('Requested channel: %s, not found',name) 
            end
            
            chan = temp.getChannelByName(name,in);

        end
        function exportToMatFile(obj,save_path)
           %NYI 
        end
    end
    
end

