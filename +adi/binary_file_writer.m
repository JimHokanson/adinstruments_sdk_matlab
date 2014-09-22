classdef binary_file_writer
    %
    %   Class:
    %   adi.binary_header
    
    %{
    Each channel header has the following format:
    type name description
    char Title[32] channel title
    char Units[32] units name
    double scale see text
    double offset see text
    double RangeHigh see text
    double RangeLow see text

    %}
    
    properties
       file_path
       date_number
       pre_trigger_time = 0 %pre_rigger time in seconds
       %time_channel - 1 => time included, how would that happen?
       %which one is the time channel?
       %
    end
    
    properties (Dependent)
       fs %Check all channels, use the highest rate
    end
    
    methods
        function obj = binary_file_writer(file_path)
           obj.file_path = file_path; 
        end
        function write(obj)
           %Checks:
           %- at least 1 channel is defined
           
           fid = fopen(obj.file_path,'w'); 
        end
    end
    
end

