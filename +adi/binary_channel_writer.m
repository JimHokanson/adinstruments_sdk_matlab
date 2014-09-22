classdef binary_channel_writer
    
    properties
        name
        units
        %These are only needed for 16 bit data, although they must be in
        %the binary.
        scale  = 1
        offset = 0
    end
    
    methods
    end
    
end

