classdef channel_data < handle
    %
    %   Class:
    %   adinstruments.channel_data
    %
    %
    %   TODO: Change channel_ploter out for this function ...
    %
    %   TODO: The lineplot reducer code is driving me nuts with the speed.
    %   This needs to be fixed ...
    
    properties
        channel_specs_obj
        record_id
        current_units
        time_obj
    end
    
    properties
        data
    end

    methods
        function obj = channel_data(channel_specs_obj,record_id,varargin)
            %
            %   obj = adinstruments.channel_data(channel_specs,record_id)
            
            in.gain         = 1;  %Gain that needs to be removed ...
            in.input_units  = 'V';
            in.output_units = 'uV';
            in.filterer     = [];
            in = sl.in.processVarargin(in,varargin);
            
            
            obj.channel_specs_obj = channel_specs_obj;
            obj.record_id = record_id;
            
            if strcmp(in.input_units,in.output_units)
                scale_factor = 1; %This is a quick hack ...
            else
            scale_factor = 1e6; %TODO: Have units class that allows
            %translation from one set of units to another ....
            end
            
            temp_data = channel_specs_obj.getAllData(record_id)*(scale_factor/in.gain);
            
            obj.current_units = in.output_units;
            
            dt = obj.channel_specs_obj.dt(obj.record_id);
            
            obj.time_obj = sci.time_series.time(dt,length(temp_data));
            
            
            if isobject(in.filterer)
                obj.data = in.filterer.filter(temp_data,'fs',obj.time_obj.fs);
            else
                obj.data = temp_data;
            end
            
        end
        function plot(obj)
           lpr_fh = @sl.plot.big_data.LinePlotReducer;

           %TODO: Pass in only instructions of time instead ...
           lpr = lpr_fh(obj.time_obj.getTimeArray,obj.data);

           lpr.renderData()
        end
    end
    
end

