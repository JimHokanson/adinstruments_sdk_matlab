# Writing 

I have not tested this extensively. Suggestions welcome.

LabChart supports at least 3 different file types:

1. **.adibin** - a very simple binary format with only 1 record and no events
2. **.adidat** - a more complex format that supports multiple records and events
3. **.adicht** - the standard LabChart file format that includes not only data (like adidat) but also settings. Writing directly to this format is not supported.

I haven't tested this but my impression is that you can switch formats if need be using LabChart.

**If you want to write to a .adicht file, write to .adidat and convert using LabChart**

# Limitations #

- It should be possible to move comments, but I haven't figured out how. I can't remember if it is a bug with the API or with my code
- Sampling must be at a fixed rate

# ADIBIN writing #

```
      file_path = 'C:\repos\test_bin.adibin';
      obj = adi.binary_file_writer(file_path)
      %FORMAT: channel name, units, sampling_rate, data
      obj.addNewChannel('Pressure','cmH2O',1000,1:2000);
      obj.addNewChannel('EUS EMG Corrected','mV',20000,1:40000);
      obj.addNewChannel('Stim','V',20000,1:40000);
      obj.write();
```

# ADIDAT writing #

Here's an example.

Note, I recommend that you don't add all of your samples at once. If you want to write a lot of data call addSamples in a loop. My impression is that there is a compression call when adding samples and if you add too many the compression fails (see issue #???)

```
      file_path = 'D:\repos\test.adidat';
      fw = adi.createFile(file_path); %fw : file_writer
    
      fs1 = 100;
      chan = 1;
      pres_chan = fw.addChannel(chan,'pressure',fs1,'cmH20');
    
      fs2 = 1000;
      chan = 2;
      emg_chan = fw.addChannel(chan,'emg',fs2,'mV');
    
      start_date_time = datenum(2023,7,19,18,0,0);
      fw.startRecord('trigger_time',start_date_time);
    
      y1 = [1:1/fs1:10 10:-1/fs1:1 1:1/fs1:10 10:-1/fs1:1];
      pres_chan.addSamples(y1);
      
      %Note record gets truncated to shortest channel
      t = (1:length(y1)*(fs2/fs1)).*1/fs2;
      y2 = sin(2*pi*1/10*t);
      emg_chan.addSamples(y2);
    
      fw.stopRecord();
	  
	  %Repeat startRecord and stopRecord if you want to add more
    
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
	  
	  %Or this should work
      %fw.saveAndClose();
```

Note, the writing process locks the file. If you want to view it in LabChart you should call:

```
clear fw emg_chan pres_chan %modify based on your variables
%OR
clearvars
```
