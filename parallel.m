if isempty(gcp('nocreat'))
parpool(maxNumCompThreads);
end