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
            
            file = adinstruments.file(file_path,file_handle);
            
        end
        function closeFile(file_handle)
            %
            %
            %   Status: Causing problems   
            
           result_code = adinstruments.sdk_mex(13,file_handle); 
        end
        function n_records = getNumberOfRecords(file_handle)
            %
            %
            %   n_records = adinstruments.sdk.getNumberOfRecords(file_handle)
            %
            %   Status: DONE
            
            
            [result_code,n_records] = adinstruments.sdk_mex(1,file_handle);
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
            n_ticks_in_record = double(n_ticks_in_record);
            
        end
        function s_per_tick = getTickPeriod(file_handle)
            %
            %
            %   
            
            [result_code,s_per_tick] = adinstruments.sdk_mex(4,file_handle,record_idx_0b);
        end
        function n_samples = getNSamplesInRecord(file_handle)
           [result_code,n_samples] = adinstruments.sdk_mex
        end
        function resolveErrorCode()
           %NOT YET IMPLEMENTED
        end
    end
    
end

