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
        %   value - file path
        path_key_map
        %
        %   key - file path
        %   value - count of how many are open
    end
    
    methods
        function obj = handle_manager()
            obj.map = containers.Map('KeyType','int32','ValueType','char');
            obj.path_key_map = containers.Map('KeyType','char','ValueType','any');
        end
    end
    
    methods (Static)
        function pointer_value = checkFilePointer(file_path)
            %   pointer_value = adi.handle_manager.checkFilePointer(file_path)
            %
            %   This gets called on opening a file using the ADI sdk. If 
            %   a file is already open, we return its pointer, rather
            %   than creating a new pointer for the file.
            %
            %   If a file is not already open, then we return 0, indicating
            %   that a new pointer should be requested from the SDK.
            %   
            %   Inputs:
            %   -------
            %   file_path = 
            %
            %   See Also:
            %   adi.sdk.openFile
            
            pointer_value = 0;
            
%            obj = adi.handle_manager.getReference();
%            if obj.path_key_map.isKey(file_path)
%                temp = obj.path_key_map(file_path);
%                pointer_value = temp(1);
%                temp(2) = temp(2) + 1;
%                obj.path_key_map(file_path) = temp;
%            else
%                pointer_value = 0;
%            end
           
        end
        function openFile(file_path,pointer_value)
            %
            %   adi.handle_manager.openFile(file_path,pointer_value)
            %
            %   See Also:
            %   adi.sdk.openFile
            
            obj = adi.handle_manager.getReference();
            if obj.map.isKey(pointer_value)
                error('Pointer value is redundant, this is not expected')
            end
            obj.map(pointer_value) = file_path;
            
            %[pointer_value  count]
            %obj.path_key_map(file_path) = [pointer_value 1];
        end
        function closeFile(pointer_value)
            %
            %    adi.handle_manager.closeFile(pointer_value)
            %
            %   See Also:
            %   adi.sdk.closeFile
            
            obj = adi.handle_manager.getReference();
            if obj.map.isKey(pointer_value)
                file_path = obj.map(pointer_value);
                
                obj.map.remove(pointer_value);
                result_code = sdk_mex(13,pointer_value);
                adi.sdk.handleErrorCode(result_code);

% % %                 temp = obj.path_key_map(file_path);
% % %                 if temp(2) == 1
% % %                     obj.map.remove(pointer_value);
% % %                     obj.path_key_map.remove(file_path);
% % %                     result_code = sdk_mex(13,pointer_value);
% % %                     adi.sdk.handleErrorCode(result_code);
% % %                 else
% % %                    temp(2) = temp(2) - 1;
% % %                    obj.path_key_map(file_path) = temp;
% % %                 end
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

