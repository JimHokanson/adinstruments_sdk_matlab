function mask = contains(data,strings_or_patterns,varargin)
%x Returns mask on whether each string contains the pattern
%
%   mask = sl.cellstr.contains(data,strings_or_patterns,varargin)
%
%   Note the current behavior is to 'or' the responses such that a match to
%   any pattern will return true. 
%
%   Determine for each 'data' whether the 'strings_or_patterns' is 
%   contained in it.
%
%   Inputs:
%   -------
%   data : cellstr
%   strings_or_patterns : char or cellstr
%       
%   Optional Inputs:
%   ----------------
%   case_sensitive : logical (default false)
%   regexp : logical (default false)
%
%       The default behavior is to OR the matches, i.e. true if any of
%       the strings match. For AND, all the strings must match.
%   use_or: logical (default [])
%       - true - OR
%       - false - AND
%   use_and: logical (default [])
%       - true - AND
%       - false - OR
%   
%   Improvements:
%   -------------
%   1) Allow specifying a regxp flag for every pattern (i.e. 'regexp' would
%   be an array)
%
%
%   Examples:
%   ---------
%   1)
%   data = {'this is a test','example I am','cheeseburger'}
%   strings = {'test' 'cheese'};
%   mask = sl.cellstr.contains(data,strings)
%   mask => [1 0 1]
%
%   2) 
%   data = {'qp1','this is a qp','qp today'}
%   patterns = {'^qp\s*\d+'}
%   mask = sl.cellstr.contains(data,patterns,'regexp','true')
%   mask => [1 0 0]
%
%   3)
%   data = {'this is a test','test'}
%   strings = {'this','test'}
%   %Both true, because we match one of the patterns
%   mask = sl.cellstr.contains(data,strings_or_patterns,'use_or',true)
%   %Only the first one is true, because it contains both patterns
%   mask = sl.cellstr.contains(data,strings,'use_and',true)
%
%   See Also:
%   ---------
%   sl.str.contains

%The idea with flag is to return indices of matches for many to many 
%searches. Essentially, this would be like ismember() but with support
%for partial matches. I think instead of implementing this I just did the 
%index search on my output ...
%
%   data = {'test' 'cheese' 'nope'}
%   strings = {'asdf' 'school' 'bib 'testing' 'cheddar cheese'}
%
%   Instead pf 
%
% in.return_match_index = false; NYI
in.use_or = []; 
in.use_and = [];
in.case_sensitive = false;
in.regexp = false;
in = adi.sl.in.processVarargin(in,varargin);

if isempty(in.use_or) && isempty(in.use_and)
    or_results = true;
elseif ~isempty(in.use_or)
    or_results = in.use_or;
else
    or_results = ~in.use_and;
end

if in.case_sensitive
    fh = @regexp;
else
    fh = @regexpi;
end

if ~iscell(data)
    error('Input data must be a cellstr')
end

if ischar(strings_or_patterns)
    strings_or_patterns = {strings_or_patterns};
end

n_patterns = length(strings_or_patterns);
if n_patterns == 0
    mask = false(1,length(data));
    return
elseif or_results
    mask = false(1,length(data));
else
	mask = true(1,length(data));
end

% if in.return_match_index
%     output_I = zeros(1,length(data)); 
% end

for iPattern = 1:length(strings_or_patterns)
    cur_str_or_pattern = strings_or_patterns{iPattern};
    
    if ~in.regexp
       cur_str_or_pattern = regexptranslate('escape',cur_str_or_pattern);
    end

    temp_mask = mask;
    
    %In this case we test only the ones that we need to ...
    %negating cur_mask provides an 'or' function rather than not negating
    %which would do 'and'
    if or_results
        process_mask = ~mask;
    else
        process_mask = mask;
    end
    
    data_to_test = data(process_mask);
    match_I = fh(data_to_test,cur_str_or_pattern,'once');
    mask(process_mask) = ~cellfun('isempty',match_I);
end

% if output_I
%     
% end

end