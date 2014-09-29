classdef (Hidden) binary_channel_writer
    %
    %   Class:
    %   adi.binary_channel_writer
    %
    %   See Also:
    %   adi.binary_file_writer
  
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
        name
        units
        %These are only needed for 16 bit data, although they must be in
        %the binary.
        scale  = 1
        offset = 0
    end
    
    methods
        function obj = binary_channel_writer(channel_name,units)
           obj.name  = channel_name;
           obj.units = units;
        end
        function write(obj,fid)
           %pass 
        end
    end
    
end

