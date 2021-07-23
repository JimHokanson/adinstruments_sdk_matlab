# Changes #

## 2021-07-23 ##

- Fixed pragma warnings (issue #14)
- Updated documentation
- Added support for versioning the mat file

```
%Save as -v6 rather than the default, -v7.3
options = adi.mat_conversion_options;
options.version = '-v6';
adi.convert(file_path,'conversion_options',options);
```