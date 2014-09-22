classdef (Hidden) test_SDK
    %
    %   Class:
    %   adi.test_SDK
    %
    %   Run as:
    %   adi.test_SDK.run_tests
    
    properties
    end
    
    methods (Static)
        function run_tests()
           %
           %
           %    adi.test_SDK.run_tests
           
           COPY_BLANK = false;
           
           %This code might move or the function might be renamed ...
           temp_file_path = [tempname() '.adicht'];
           disp(temp_file_path)
           
           file_writer = adi.createFile(temp_file_path,COPY_BLANK);
           
           fw = file_writer; %Let's shorten things
           
           pres_chan = fw.addChannel(1,'pressure',1000,'cmH20');
           
           fw.startRecord();
           
           pres_chan.addSamples(1:1000);
           
           fw.stopRecord();
           
           fw.save();
           fw.close();
           
           %TODO: I think I need to delete the temp file from the disk
        end
    end
    
end

