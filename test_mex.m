%Assumes file_path is already defined

adinstruments.sdk.make_mex()

adfile = adinstruments.sdk.openFile(file_path);

%These will be moved to being properties of adfile ...
n_records = adinstruments.sdk.getNumberOfRecords(adfile.file_handle);

n_channels = adinstruments.sdk.getNumberOfChannels(adfile.file_handle);


%f = sdk_test(2)

%[c,d] = adinstruments.sdk_mex(1,b)