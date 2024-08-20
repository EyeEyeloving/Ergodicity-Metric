clear
clc

agt_nums = 10; % the number of agents for demonstration
fs = 1000; % sampling frequency
TaskTime = 30; % task time
k_r = 5; % the resolution of fourier basis

filelist = dir('../../dat/');
for i = 1:agt_nums
    filename = strcat('../../dat/', filelist(i+2).name);
    agt_imit(i).dat_txtarray = load(filename);

    minXVec(i) = min(agt_imit(i).dat_txtarray(:, 1));
    maxXVec(i) = max(agt_imit(i).dat_txtarray(:, 1));
    minZVec(i) = min(agt_imit(i).dat_txtarray(:, 3));
    maxZVec(i) = max(agt_imit(i).dat_txtarray(:, 3));
    % clear obj_agt
end

% move the trajectory from [a, b] to [0, b-a]
mminXVec = min(minXVec); mmaxXVec = max(maxXVec);
domainUX = mmaxXVec - mminXVec;
mminZVec = min(minZVec); mmaxZVec = max(maxZVec);
domainUZ = mmaxZVec - mminZVec;
for i = 1:agt_nums
    agt_imit(i).xp1 = agt_imit(i).dat_txtarray(:, 1)-mminXVec;
    agt_imit(i).xp2 = agt_imit(i).dat_txtarray(:, 3)-mminZVec;
end

theErgo = ERGODICITYCostMetric(k_r);
theErgo.domainUX = domainUX;
theErgo.domainUZ = domainUZ;
theErgo.agents_sampling_numberlong = fs*TaskTime;
theErgo.agents_sampling_timglong = TaskTime;

Phik = zeros(k_r+1);
for i = 1:agt_nums
    Sigmak = theErgo.FitSigmak(agt_imit(i).xp1, agt_imit(i).xp2);
    Phik = Sigmak + Phik;
end
Phik = Phik./agt_nums;
