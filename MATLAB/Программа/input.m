load 2;
r = size(Real);
realCounter(1,1) = 1;
realCounter(1,2) = 1;
for i = 1 :r(2)
    s = size(Real(i).t);
    realCounter(i,1) = 1;
    realCounter(i,2) = s(2);
end

h = size(Hypo);
hypoCounter(1,1) = 1;
hypoCounter(1,2) = 1;
for i = 1 :h(2)
    s = size(Hypo(i).t);
    hypoCounter(i,1) = 1;
    hypoCounter(i,2) = s(2);
    hypoCounter(i,3) = 0;
end

s = size(POI.t);
 poiCounter(1,1) = 1;
 poiCounter(1,2) = s(2);
 poiCounter(1,3) = 0;
 
 s = size(Noize.t);
 noizeCounter(1,1) = 1;
 noizeCounter(1,2) = s(2);
 noizeCounter(1,3) = 0;

v = size(VOI);
flag = 0;
 voiCounter(i,1) = 1;
 voiCounter(i,2) = 1;
for i = 1 : v(2)
    s = size(VOI(i).t);
    voiCounter(i,1) = 1;
    voiCounter(i,2) = s(2);
    voiCounter(i,3) =0;
end
j = 1;
while(flag~=1)
    if(poiCounter(1,2) < poiCounter(1,1))
        break;
    end
    if(noizeCounter(1,2) < noizeCounter(1,1))
        break;
    end
    delta(1) = POI.t(poiCounter(1,1));
    delta(2) = 3;
    delta(3) = 1;
    
    if(noizeCounter(1,2) >= noizeCounter(1,1) && delta(1) >= Noize(1).t(noizeCounter(1,1)))
            delta(1) = Noize.t(noizeCounter(1,1));
            delta(2) = 5;
            delta(3) = 1;
    else
            if(noizeCounter(1,2) < noizeCounter(1,1))
                flag = 1;
            end     
    end
    
    
%     for i = 1:h(2)
%         if(hypoCounter(i,2) >= hypoCounter(i,1) && delta(1) >= Hypo(i).t(hypoCounter(i,1)))
%             delta(1) = Hypo(i).t(hypoCounter(i,1));
%             delta(2) = 2;
%             delta(3) = i;
%         end
%     end
%     for i = 1:v(2)
%         if(voiCounter(i,2) >= voiCounter(i,1) && delta(1) >= VOI(i).t(voiCounter(i,1)))
%             delta(1) = VOI(i).t(voiCounter(i,1));
%             delta(2) = 4;
%             delta(3) = i;
%         else
%             if(voiCounter(i,2) < voiCounter(i,1))
%                 flag = 1;
%             end     
%         end
%     end
    
    cla('reset');
    if(poiCounter(1,2) >= poiCounter(1,1) && poiCounter(1,3) == 1)
        plot3(POI.x(1:poiCounter(1,1)),POI.y(1:poiCounter(1,1)),POI.z(1:poiCounter(1,1)),'.r');
    end
    hold on;
    grid on;
    if(noizeCounter(1,2) >= noizeCounter(1,1) && noizeCounter(1,3) == 1)
        plot3(Noize.x(1:noizeCounter(1,1)),Noize.y(1:noizeCounter(1,1)),Noize.z(1:noizeCounter(1,1)),'.r');
    end
%     for i = 1:h(2)
%         if(hypoCounter(i,2) >= hypoCounter(i,1) && hypoCounter(i,3) == 1)
%             plot3(Hypo(i).x(1:hypoCounter(i,1)),Hypo(i).y(1:hypoCounter(i,1)),Hypo(i).z(1:hypoCounter(i,1)),'-.x');
%         end
%     end
%     for i = 1:v(2)
%         if(voiCounter(i,3) == 1 && voiCounter(i,2) >= voiCounter(i,1))
%         plot3(VOI(i).x(1:voiCounter(i,1)),VOI(i).y(1:voiCounter(i,1)),VOI(i).z(1:voiCounter(i,1)),'--x');
%         end
%     end
    
    %axis([8000,16000,1000,6000,5000,30000]);
    axis([8000,14000,1400,5000,10000,28000]);
%     j = j + 1;
%     view( [ j,25 ] );
    pause(0.00002);
    switch(delta(2))
%        case 2
%             for i = 1:h(2)
%                 if(delta(3) == i)
%                     hypoCounter(i,1) = hypoCounter(i,1) + 1;
%                     hypoCounter(i,3) = 1;
%                 end
%             end
        case 3
            poiCounter(1,1) = poiCounter(1,1) + 1;
            poiCounter(1,3) = 1;
%         case 4
%             for i = 1:v(2)
%                 if(delta(3) == i)
%                      voiCounter(i,1) = voiCounter(i,1) + 1;
%                     voiCounter(i,3) = 1;
%                 end
%             end
        case 5
            noizeCounter(1,1) = noizeCounter(1,1) + 1;
            noizeCounter(1,3) = 1;
    end
    
end

pause(2);
flag = 0;
while(1)
    j = j + 1;
    view( [ j,25 ] );
    pause(0.02);
    if (flag == 0)
        for i = 1:r(2)   
            plot3(Real(i).x,Real(i).y,Real(i).z,'-p');
        end
        flag = 1;
    end
end