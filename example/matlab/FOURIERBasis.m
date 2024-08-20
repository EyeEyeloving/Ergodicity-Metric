classdef FOURIERBasis
    %FOURIERBASIS 此处显示有关此类的摘要
    %   此处显示详细说明
    
    properties (SetAccess = public)
        domainUX = 0;
        domainUZ = 0;
        agents_sampling_numberlong = 0;
        agents_sampling_timglong = 0;
    end
    
    methods
        function obj = FOURIERBasis(...
                domainUX, domainUZ, sampling_numberlong, sampling_timglong)
            if nargin > 0
                obj.domainUX = domainUX;
                obj.domainUZ = domainUZ;
                obj.agents_sampling_numberlong = sampling_numberlong;
                obj.agents_sampling_timglong = sampling_timglong;
            end
        end
        
        function integral_trapz = FitFourierBasis(obj, rp1, rp2, xp1, xp2)
            fp1 = rp1 * pi / obj.domainUX;
            fp2 = rp2 * pi / obj.domainUZ;

            allHk = FitAllHk(obj, fp1, fp2);
            Fkx = @(traj_x1, traj_x2) (1/allHk * cos(fp1*traj_x1).*cos(fp2*traj_x2));

            timestamp_array = linspace(0, obj.agents_sampling_timglong, obj.agents_sampling_numberlong);
            integral_trapz = 1/obj.agents_sampling_timglong * trapz(timestamp_array, Fkx(xp1, xp2));
        end

        function allHk = FitAllHk(obj, rp1, rp2)
            hk_integrand = @(dm_l1, dm_l2) ( (cos(rp1.*dm_l1).^2).*(cos(rp2.*dm_l2).^2));
            allHk = sqrt(integral2(hk_integrand, 0, obj.domainUX, 0, obj.domainUZ));
        end
    end
end
