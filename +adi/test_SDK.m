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
            %
            %    See Also:
            
            %This is a simple write test which eventually should be moved to
            %its own function ...
            
            
            
        end
        function writeChannelTest()
            
            file_path = 'C:\repos\test.adidat';
            fw = adi.createFile(file_path); %fw : file_writer
            
            fs1 = 100;
            chan = 1;
            pres_chan = fw.addChannel(chan,'pressure',fs1,'cmH20');
            
            fs2 = 1000;
            chan = 2;
            emg_chan = fw.addChannel(chan,'emg',fs2,'mV');
            
            fw.startRecord();
            
            y1 = [1:1/fs1:10 10:-1/fs1:1 1:1/fs1:10 10:-1/fs1:1];
            pres_chan.addSamples(y1);
            
            %record gets truncated to shortest channel
            t = (1:length(y1)*(fs2/fs1)).*1/fs2;
            y2 = sin(2*pi*1/10*t);
            emg_chan.addSamples(y2);
            
            fw.stopRecord();
            
            comment_time = 2;
            comment_string = 'Best EMG signal ever!';
            record = -1; %-1 is current record (or last record if stopped)
            comment_channel = 2;
            fw.addComment(record,comment_time,comment_string,'channel',comment_channel);
            
            comment_time = 9;
            comment_string = 'Best time ever';
            record = -1; %-1 is current record (or last record if stopped)
            comment_channel = -1;
            fw.addComment(record,comment_time,comment_string,'channel',comment_channel);
            fw.save();
            fw.close();
            
            clear fw emg_chan pres_chan %if you want to open it in ADInstruments
            %or this
            %clearvars
            
            %Or this should work
            %fw.saveAndClose();
            
        end
    end
    
end

