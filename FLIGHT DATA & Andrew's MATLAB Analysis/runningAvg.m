radiusOfAverage=125; % set the radius of our average. radius of 25 means a 50-pt average
ra_OldEOSSAltVsTemp2=zeros((14560-radiusOfAverage*2),2); % allocate a var to hold finished data

sampleSum=0; % declare this for later

% if we're doing an average with r=25, then we can't use the ends of our original data because there's not 25 points on either side of, say, the 2nd index. We account for this here
for index=radiusOfAverage+1:14560-(radiusOfAverage)

    % go through and sum the points on either side
    for sample=index-radiusOfAverage:index+radiusOfAverage
        sampleSum=sampleSum+OldEOSSAltVsTemp2(sample,2);
    end

    % in that variable we allocated earlier, write the same mission time as the point around which our average is centered. then, in the adjacent column, put the average of the sum from above (don't forget that we technically summed 51 points!)
    ra_OldEOSSAltVsTemp2(index-radiusOfAverage,1)=OldEOSSAltVsTemp2(sample,1);
    ra_OldEOSSAltVsTemp2(index-radiusOfAverage,2)=sampleSum/(radiusOfAverage*2+1);

    % rinse and repeat
    sampleSum=0;

end

% plot it for fun:

scatter(ra_OldEOSSAltVsTemp2(:,1),ra_OldEOSSAltVsTemp2(:,2),40,'.')

clear index sample sampleSum radiusOfAverage