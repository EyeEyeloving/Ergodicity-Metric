classdef ERGODICITYCostMetric < FOURIERBasis
    %ERGODICITYCOSTMETRIC 此处显示有关此类的摘要
    %   此处显示详细说明
    
    properties (SetAccess = public)
        k_resolution;
        agents_expertnumber;
    end
    
    methods
        function obj = ERGODICITYCostMetric(k_r)
            if nargin>0
                obj.k_resolution = k_r;
            end
        end
        
        function result_epsilon = FitMetric(obj, xp1, xp2, Phik)
            n_dimension = 2;
            result_epsilon = 0;

            for rp1 = 0:obj.k_resolution
                for rp2 = 0:obj.k_resolution
                    GAMMA_r = ((1 + norm([rp1, rp2])^2)^( -(n_dimension+1)/2));
                    sigma_r = FitFourierBasis(obj, rp1, rp2, xp1, xp2);
                    result_epsilon = GAMMA_r * norm(sigma_r - Phik(rp1+1, rp2+1))^2 + result_epsilon;
                    
                    clc;
                    fprintf('[Ergodicity Metric Calculation]: ');
                    fprintf('k1 = %d, k2 = %d \n', rp1, rp2);
                end
            end
        end

        function Sigmak = FitSigmak(obj, xp1, xp2)
            Sigmak = zeros(obj.k_resolution+1);
            for rp1 = 0:obj.k_resolution
                for rp2 = 0:obj.k_resolution
                    Sigmak(rp1+1, rp2+1) = FitFourierBasis(obj, rp1, rp2, xp1, xp2);

                    clc;
                    fprintf('[FourierBasis Calculation]: ');
                    fprintf('k1 = %d, k2 = %d \n', rp1, rp2);
                end
            end

        end
    end
end

