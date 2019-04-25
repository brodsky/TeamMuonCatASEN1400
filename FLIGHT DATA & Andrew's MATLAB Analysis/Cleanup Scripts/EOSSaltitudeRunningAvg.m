radiusOfAverage=25;
runAvgCountsVsMins=zeros((height(GEIGERFLIGHT)-radiusOfAverage*2),2);

sampleSum=0;

for index=radiusOfAverage+1:height(GEIGERFLIGHT)-(radiusOfAverage+1)
    
    for sample=index-radiusOfAverage:index+radiusOfAverage
        sampleSum=sampleSum+GEIGERFLIGHT.MuonCount(sample);
    end
    
    runAvgCountsVsMins(index-radiusOfAverage,1)=GEIGERFLIGHT.MissionMins(index);
    runAvgCountsVsMins(index-radiusOfAverage,2)=sampleSum/(radiusOfAverage*2+1);
    
    sampleSum=0;
    
end

scatter(runAvgCountsVsMins(:,1),runAvgCountsVsMins(:,2),60,'.')
title('Muon Counts Per Minute vs Altitude (50-Point Running Average, Ascent Only)');
xlabel('Altitude (m)');
ylabel('Muon Counts Per Minute (min)^-1');
legend('Geiger Counter Data');
set(gca,'fontsize', 13, 'fontweight', 'bold');

clear index sample sampleSum radiusOfAverage
        
        
        
        
        