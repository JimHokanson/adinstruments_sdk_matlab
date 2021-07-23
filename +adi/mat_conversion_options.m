classdef mat_conversion_options
    %
    %   Class:
    %   adi.mat_conversion_options
    
    properties
        partial_read = false %Not Yet Implemented
        %The goal was to partial read/writes of channels to disk
        %rather than loading everything at once and dumping in one write.
        version = '-v7.3';
        %{
            Option   | Versions     | Supported Features
            ---------+--------------+----------------------------------------------
            '-v7.3'  | 7.3 or later | Version 7.0 features plus support for
                     |              | data items greater than or equal to 2GB on
                     |              | 64-bit systems. This version also supports 
                     |              | saving variables without compression using 
                     |              | the '-nocompression' flag. 
            ---------+--------------+----------------------------------------------
            '-v7'    | 7.0 or later | Version 6 features plus data compression and
                     |              | Unicode character encoding
            ---------+--------------+----------------------------------------------
            '-v6'    | 5 or later   | Version 4 features plus N-dimensional arrays,
                     |              | cell and structure arrays, and variable names
                     |              | greater than 19 characters
        %}
    end
    
    methods
        function verify(obj)
            obj.verifyVersion()
        end
        function verifyVersion(obj)
            switch lower(obj.version)
                case '-v7.3'
                case '-v7'
                case '-v6'
                case '-v4'
                    error('This version is not supported')
                otherwise
                    error('Version "%s" not recognized',obj.version)
            end
        end
    end
    
end

