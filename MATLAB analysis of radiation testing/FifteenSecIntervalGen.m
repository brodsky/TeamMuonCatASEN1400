% This script takes in a cleaned count matrix from the RadiationCalibration
% workspace and calculates the CPM over 8 different 15-second intervals
% (assuming that the data are spaced evenly with respect to time). The
% average CPM is also computed.

% The name of the input matrix should go here:
inputFile='CleanCountsfromC1at1mNoShield';

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
fprintf('For file %s: \n \n',(inputFile));

% Figure out how many data points should go into each new (smaller) matrix
divInterval=floor(eval(['length(',inputFile,')'])/8);

m1=(eval([inputFile,'(1:divInterval)']));
m2=(eval([inputFile,'(divInterval+1:2*divInterval)']));
m3=(eval([inputFile,'(2*divInterval+1:3*divInterval)']));
m4=(eval([inputFile,'(3*divInterval+1:4*divInterval)']));
m5=(eval([inputFile,'(4*divInterval+1:5*divInterval)']));
m6=(eval([inputFile,'(5*divInterval+1:6*divInterval)']));
m7=(eval([inputFile,'(6*divInterval+1:7*divInterval)']));
m8=(eval([inputFile,'(7*divInterval+1:end)']));

avg1=sum(m1)*4;
avg2=sum(m2)*4;
avg3=sum(m3)*4;
avg4=sum(m4)*4;
avg5=sum(m5)*4;
avg6=sum(m6)*4;
avg7=sum(m7)*4;
avg8=sum(m8)*4;
totalAvg=(eval(['sum(',inputFile,')/2']));

fprintf('Interval 1: %i CPM \n',(avg1));
fprintf('Interval 2: %i CPM \n',(avg2));
fprintf('Interval 3: %i CPM \n',(avg3));
fprintf('Interval 4: %i CPM \n',(avg4));
fprintf('Interval 5: %i CPM \n',(avg5));
fprintf('Interval 6: %i CPM \n',(avg6));
fprintf('Interval 7: %i CPM \n',(avg7));
fprintf('Interval 8: %i CPM \n',(avg8));
fprintf('\nOverall Average: %.2f CPM \n',(totalAvg));

clear inputFile divInterval m1 m2 m3 m4 m5 m6 m7 m8 avg1 avg2 avg3 avg4 avg5 avg6 avg7 avg8 totalAvg
