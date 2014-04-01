classdef sdk
    %UNTITLED Summary of this class goes here
    %   Detailed explanation goes here
    
    %http://www.mathworks.com/help/matlab/matlab_external/passing-arguments-to-shared-library-functions.html#f44412
    
    properties
    end

    methods (Static)
        function init()
            %
            %   adinstruments.sdk.init()
            %TODO: Get base path automatically
            %TODO: Check if lib is loaded first ...
            %TODO: Fix warning in header
           lib_path = 'C:\Users\Jim\Documents\ADInstruments\SimpleDataFileSDK\bin\ADIDatIOWin.dll';
            hdr_path = 'C:\Users\Jim\Documents\ADInstruments\SimpleDataFileSDK\adidat\include\ADIDatCAPI_ml.h';

            %unloadlibrary('ADIDatIOWin')
            loadlibrary(lib_path,hdr_path,'mfilename','wtf.m')
            %loadlibrary(lib_path,@wtf) %'mfilename','wtf.m') 
        end
        function openFile(file_path,is_read_only)
           %
           %     adinstruments.sdk.openFile(file_path,true)
           %
           %
           %
           
          % wtf = libpointer('ADI_FileHandle__Ptr');
           %file_handle_pointer = libpointer('voidPtr',wtf);
           file_handle_pointer = libpointer('ADI_FileHandle__PtrPtr');
            
           %wtf = libpointer('voidPtr',int32(0));
           if is_read_only
               file_open_mode = 0; %'kOpenFileForReadOnly';
           else
               file_open_mode = 1; %'kOpenFileForReadAndWrite';
           end
           %result = calllib('ADIDatIOWin','ADI_OpenFile',int16(file_path),file_handle_pointer,file_open_mode);
           
           result = calllib('ADIDatIOWin','ADI_OpenFile',int16(file_path),wtf,file_open_mode);
           %0 - failure
           keyboard
           temp = get(file_handle_pointer,'Value');
           fprintf('file_id: %d\n',temp.unused);
           if ischar(result)
           fprintf('Result: %s\n',result)
           else
             fprintf('Result: %d\n',result)  
           end
        end
        function getNumberOfRecords()
            %
            %
            %   adinstruments.sdk.getNumberOfRecords()
            %
            %wtf = libpointer('voidPtr',int16(-2012));
            wtf = struct('unused',int32(1654585380));
            
            wtf3 = int32(1650391076);
            
            wtf2 = libpointer('voidPtr',wtf);
            
            s = struct('unused',int32(1654585380));
            
            file_handle_pointer = libpointer('ADI_FileHandle__Ptr');
            set(file_handle_pointer,'Value',struct('unused',int32(0)))
            
            n_records_pointer = libpointer('longPtr');
            %result = calllib('ADIDatIOWin','ADI_GetNumberOfRecords',file_handle_pointer,n_records_pointer);
            result = calllib('ADIDatIOWin','ADI_GetNumberOfRecords',wtf3,n_records_pointer);
        end
        function getNumberOfChannels()
            wtf3 = int32(1650391076);
            file_handle_pointer = libpointer('ADI_FileHandle__Ptr');
            set(file_handle_pointer,'Value',struct('unused',int32(1474689060)))
            n_channels_pointer = libpointer('longPtr');
            result = calllib('ADIDatIOWin','ADI_GetNumberOfChannels',wtf3,n_channels_pointer);
           %ADI_GetNumberOfChannels(ADI_FileHandle fileH, long* nChannels); 
        end
        function resolveErrorCode()
            
            %Goal is to go from string or values to a string response
            
            %Got: dec2hex(typecast(int32(-2147024894),'uint32'))
            
            
            %{
            typedef enum ADIResultCode
      {
      //Win32 error codes (HRESULTs)
      kResultSuccess = 0,                             // operation succeeded
      kResultErrorFlagBit        = 0x80000000L,       // high bit set if operation failed
      kResultInvalidArg          = 0x80070057L,       // invalid argument. One (or more) of the arguments is invalid
      kResultFail                = 0x80004005L,       // Unspecified error
      kResultFileNotFound        = 0x80030002L,       // failure to find the specified file (check the path)


      //Start of error codes specific to this API      
      kResultADICAPIMsgBase        = 0xA0049000L,

      kResultFileIOError  = kResultADICAPIMsgBase,    // file IO error - could not read/write file
      kResultFileOpenFail,                            // file failed to open
      kResultInvalidFileHandle,                       // file handle is invalid
      kResultInvalidPosition,                         // pos specified is outside the bounds of the record or file
      kResultInvalidCommentNum,                       // invalid commentNum. Comment could not be found
      kResultNoData,                                  // the data requested was not present (e.g. no more comments in the record).
      kResultBufferTooSmall                          // the buffer passed to a function to receive data (e.g. comment text) was not big enough to receive all the data.
      
                                                      // new result codes must be added at the end
      } ADIResultCode; 
            %}
        end
    end
    
end

