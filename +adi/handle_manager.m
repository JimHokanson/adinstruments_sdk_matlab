classdef (Hidden) handle_manager
    %
    %   Class:
    %   adi.handle_manager
    %
    %   This class keeps track of open files and attempts to prevent
    %   closing a file that for some reason is not actually open.
    %   
    %
    %   See Also:
    %   adi.sdk
    
    properties
        map %containers.Map
        %
        %   key - pointer value of open file
        %   value - file path (for debugging only)
    end
    
    methods
        function obj = handle_manager()
            obj.map = containers.Map('KeyType','int32','ValueType','char');
        end
    end
    
    methods (Static)
        function openFile(file_path,pointer_value)
            %
            %   adi.handle_manager.openFile(file_path,pointer_value)
            
            obj = adi.handle_manager.getReference();
            if obj.map.isKey(pointer_value)
                error('Pointer value is redundant, this is not expected')
            end
            obj.map(pointer_value) = file_path;
        end
        function closeFile(pointer_value)
            %
            %    adi.handle_manager.closeFile(pointer_value)
            obj = adi.handle_manager.getReference();
            if obj.map.isKey(pointer_value)
                obj.map.remove(pointer_value);
                result_code = sdk_mex(13,pointer_value);
                adi.sdk.handleErrorCode(result_code);
            else
                %TODO: Move formatted warning into adi.sl
                warning('Trying to close a file whose pointer is not logged')
            end
        end
        function output_obj = getReference()
            %
            %   adi.handle_manager.getReference
            %
            persistent obj
            if isempty(obj)
                %NOTE: We lock things to try and prevent problems with
                %the mex file. I'm not sure if this is really necessary,
                %but it makes me sleep better at night :)
                mlock();
                obj = adi.handle_manager;
            end
            output_obj = obj;
        end
        function unlock()
            %adi.handle_manager.unlock
            munlock();
        end
    end
    
end

