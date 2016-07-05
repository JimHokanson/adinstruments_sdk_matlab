function e002_addCommentsToAnExistingFile()
%
%   Why doesn't this work???
%
%   Is there some problem with modifying old adicht files that
%   weren't created with the sdk?
%
%   adi.examples.e002_addCommentsToAnExistingFile

file_path = 'C:\Users\Jim\Desktop\temp_edited\test.adicht';

fw = adi.editFile(file_path);

fw.addComment(1,300,'Does this actually work?')
%fw.addComment(7,300,'Does this actually work?')


%Fails on this line
fw.save