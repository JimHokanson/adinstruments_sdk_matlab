classdef sdk
    %UNTITLED Summary of this class goes here
    %   Detailed explanation goes here
    
    %http://www.mathworks.com/help/matlab/matlab_external/passing-arguments-to-shared-library-functions.html#f44412
    
    properties
    end
    
    methods (Static,Hidden)
        function make_mex()
            %
            %   adinstruments.sdk.make_mex
            
            base_path = sl.dir.getMyBasePath;
            wd = cd;
            cd(base_path)
            try
                
                mex('sdk_mex.cpp','ADIDatIOWin.lib')
                
                %Extra files:
                %------------------------
                
                file_names = cell(1,3);
                file_names{1} = 'ADIDatIOWin_thunk_pcwin64.exp';
                file_names{2} = 'ADIDatIOWin_thunk_pcwin64.lib';
                file_names{3} = 'ADIDatIOWin_thunk_pcwin64.obj';
                
                for iFile = 1:3
                    cur_file_path = fullfile(base_path,file_names{iFile});
                    %Let's avoid a warning by checking first ...
                    if exist(cur_file_path,'file')
                        delete(cur_file_path)
                    end
                end
                
                %Go back to where we started.
                cd(wd)
            catch ME
                cd(wd)
                fprintf(2,'%s',ME.message);
            end
            
        end
    end
    
    methods (Static)
        
        function file = openFile(file_path)
            %
            %     file = adinstruments.sdk.openFile(file_path)
            %
            %   NOTE: Currently only reading is supported ...
            %
            %   STATUS: Done, except result code is not handled
            
            [result_code,file_handle] = adinstruments.sdk_mex(0,[int16(file_path) 0]);
            
            adinstruments.sdk.handleErrorCode(result_code)
            
            file = adinstruments.file(file_path,file_handle);
            
        end
        function closeFile(file_handle)
            %
            %
            %   Status: Seems Fine
            %   - I think I was running into a problem when trying
            %       to clear the file after the mex file had been cleared
            
            result_code = adinstruments.sdk_mex(13,file_handle);
            adinstruments.sdk.handleErrorCode(result_code)
        end
        function n_records = getNumberOfRecords(file_handle)
            %
            %
            %   n_records = adinstruments.sdk.getNumberOfRecords(file_handle)
            %
            %   Status: DONE
            
            
            [result_code,n_records] = adinstruments.sdk_mex(1,file_handle);
            adinstruments.sdk.handleErrorCode(result_code)
            n_records = double(n_records);
        end
        function n_channels = getNumberOfChannels(file_handle)
            %
            %
            %   n_channels = adinstruments.sdk.getNumberOfChannels(file_handle)
            %
            %   Outputs:
            %   ===========================================================
            %   n_channels : The # of physical channels of recorded data
            %   across all records. For some records some channels may not
            %   have any data. A channel is identified by (??? name ??,
            %   hardware id????)
            %
            %   Status: DONE
            
            [result_code,n_channels] = adinstruments.sdk_mex(2,file_handle);
            adinstruments.sdk.handleErrorCode(result_code)
            n_channels = double(n_channels);
        end
        function n_ticks_in_record = getNTicksInRecord(file_handle,record_idx_0b)
            %
            %
            %   Outputs:
            %   ===========================================================
            %   n_ticks_in_record : This is equivalent to asking how many
            %       samples were obtained from the channels with the highest
            %       sampling rate
            %
            %   Status: DONE
            
            [result_code,n_ticks_in_record] = adinstruments.sdk_mex(3,file_handle,int32(record_idx_0b));
            adinstruments.sdk.handleErrorCode(result_code)
            n_ticks_in_record = double(n_ticks_in_record);
            
        end
        function s_per_tick = getTickPeriod(file_handle,record_idx_0b,channel_idx_0b)
            %
            %
            %   s_per_tick = adinstruments.sdk.getTickPeriod(file_handle,record_idx_0b,channel_idx_0b)
            %
            %   Outputs:
            %   ===========================================================
            %
            %
            %   STATUS: DONE
            
            [result_code,s_per_tick] = adinstruments.sdk_mex(4,file_handle,int32(record_idx_0b),int32(channel_idx_0b));
            adinstruments.sdk.handleErrorCode(result_code)
        end
        function n_samples = getNSamplesInRecord(file_handle,record_idx_0b,channel_idx_0b)
            %
            %
            %
            %
            %   TODO: UNFINISHED
            
            [result_code,n_samples] = adinstruments.sdk_mex(5,file_handle,int32(record_idx_0b),int32(channel_idx_0b));
            adinstruments.sdk.handleErrorCode(result_code)
            n_samples = double(n_samples);
        end
        function comments_h = getCommentAccessor(file_handle,record_idx_0b)
            %
            %
            %   comments_h = adinstruments.sdk.getCommentAccessor(file_handle,record_idx_0b)
            
            [result_code,comments_h] = adinstruments.sdk_mex(6,file_handle,int32(record_idx_0b));
            if mod(result_code,16) == 5
                
                %TODO: Do I want to do the literal error check here ???
                
                %See:
                %http://forum.adinstruments.com/viewtopic.php?f=7&t=551
                
                %Then there are no comments
                %-1610313723 - data requested not present => xA0049005
                comments_h  = 0;
            else
                adinstruments.sdk.handleErrorCode(result_code)
            end
            
            %TODO: Do I want to return a comments object ...???
            
            
        end
        function closeCommentAccessor(comments_h)
            %
            %
            %   adinstruments.sdk.closeCommentAccessor(comments_h);
            
            %TODO: Do I want to check for a null comment handle
            %and ignore it or just it pass ???
            if comments_h == 0
                return
            end
            
            result_code = adinstruments.sdk_mex(7,comments_h);
            adinstruments.sdk.handleErrorCode(result_code);
        end
        function has_comment = advanceComments(comments_h)
            %
            %
            %   result_code = adinstruments.sdk.advanceComments(comments_h);
            
            %TODO: replace with better result code
            %See getCommentAccessor for similar handling ...
            
            has_comment = true;
            result_code = adinstruments.sdk_mex(9,comments_h);
            if mod(result_code,16) == 5
                has_comment = false;
            else
                adinstruments.sdk.handleErrorCode(result_code);
            end
            
        end
        function comment_info = getCommentInfo(comments_h)
            %
            %   
            %   comment_info = adinstruments.sdk.getCommentInfo(comments_h)
            
           [result_code,comment_string_data,comment_length,tick_pos,channel,comment_num] = adinstruments.sdk_mex(8,comments_h);
           if result_code == 0
               comment_string = adinstruments.sdk.getStringFromOutput(comment_string_data,comment_length);
               comment_info   = adinstruments.comment(comment_string,tick_pos,channel,comment_num);
           else 
               adinstruments.sdk.handleErrorCode(result_code);
               comment_info = [];
           end


        end
        function handleErrorCode(result_code)
            %
            %
            %   adinstruments.sdk.handleErrorCode(result_code)
            %
            %   If there is an error this function will throw an error
            %   and display the relevant error string given the error code
            
            %TODO: Allow only getting the string (make separate function)
            
            %Relevant forum post:
            %http://forum.adinstruments.com/viewtopic.php?f=7&t=551
            
            %TODO: Replace with stack evaluation to pull this out
            %automagically
            
            if result_code ~= 0
                temp      = sl.stack.calling_function_info;
                errorID   = sprintf('ADINSTRUMENTS:SDK:%s',temp.name);
                error_msg = adinstruments.sdk.getErrorMessage(result_code);
                %TODO: Create a clean id - move to a function
                
                errorID = regexprep(errorID,'\.',':');
                
                error(errorID,[errorID '  ' error_msg]);
            end
        end
        function error_msg = getErrorMessage(result_code)
            %
            %
            %   error_msg = adinstruments.sdk.getErrorMessage(result_code)
            
        	[~,err_msg_data,err_msg_len] = adinstruments.sdk_mex(14,int32(result_code));
        	error_msg = adinstruments.sdk.getStringFromOutput(err_msg_data,err_msg_len);
        end
        function str = getStringFromOutput(int16_data,str_length)
            %
            %   This is a helper function for whenever we get a string out.
            %
            %   str = adinstruments.sdk.getStringFromOutput(int16_data,str_length)
            %
            %   TODO: Make hidden
            %
            
            %str_length - apparently contains the null character, we'll
            %ignore the null character here ...
            str = char(int16_data(1:str_length-1));
        end
    end
    
end

