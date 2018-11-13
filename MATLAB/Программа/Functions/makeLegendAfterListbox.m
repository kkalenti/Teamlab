% --- ��������� ������� ����� ������ ����, �������� �� ���������� �� ������
% ������(��� ��� ����)
function makeLegendAfterListbox(handles)
    realPlot = evalin('base','realPlot');
    voiPlot = evalin('base','voiPlot');
    
    contents = get(handles.popupmenu1, 'Value');
    switch contents
        case 1
            chPoi = get(handles.checkbox4,'Value');
            chNoize = get(handles.checkbox8,'Value');
            chStrob = get(handles.checkbox12,'Value');
            if(chPoi == 0 && chNoize == 0 && chStrob == 0)
                legend([realPlot.ch1.coordinate,realPlot.ch2.coordinate,realPlot.ch3.coordinate,...
                    voiPlot.ch1.coordinate,voiPlot.ch2.coordinate,voiPlot.ch3.coordinate,],...
                    '������ x','������ y','������ z','��� x','��� y','��� z');
            end
            
            if(chPoi == 1 && chNoize == 0 && chStrob == 0)
                poiPlot = evalin('base','poiPlot');
                legend([realPlot.ch1.coordinate,realPlot.ch2.coordinate,realPlot.ch3.coordinate,...
                    voiPlot.ch1.coordinate,voiPlot.ch2.coordinate,voiPlot.ch3.coordinate,...
                    poiPlot.ch5,poiPlot.ch6,poiPlot.ch7],...
                    '������ x','������ y','������ z','��� x','��� y','��� z','��� x','��� y','��� z' );
            end
            
            if(chPoi == 0 && chNoize == 1 && chStrob == 0)
                noizePlot = evalin('base','noizePlot');
                legend([realPlot.ch1.coordinate,realPlot.ch2.coordinate,realPlot.ch3.coordinate,...
                    voiPlot.ch1.coordinate,voiPlot.ch2.coordinate,voiPlot.ch3.coordinate,...
                    noizePlot.ch9,noizePlot.ch10,noizePlot.ch11],...
                    '������ x','������ y','������ z','��� x','��� y','��� z','���� �� x','���� �� y','���� �� x');
            end
            if(chNoize == 1 && chPoi == 1 && chStrob == 0)
                noizePlot = evalin('base','noizePlot');
                poiPlot = evalin('base','poiPlot');
                legend([realPlot.ch1.coordinate,realPlot.ch2.coordinate,realPlot.ch3.coordinate,...
                    voiPlot.ch1.coordinate,voiPlot.ch2.coordinate,voiPlot.ch3.coordinate,...
                    poiPlot.ch5,poiPlot.ch6,poiPlot.ch7,...
                    noizePlot.ch9,noizePlot.ch10,noizePlot.ch11],...
                    '������ x','������ y','������ z','��� x','��� y','��� z','��� x','��� y','��� z',...
                    '���� �� x','���� �� y','���� �� x' );
            end
            
            if(chPoi == 0 && chNoize == 0 && chStrob == 1)
                strobPlot = evalin('base','strobPlot');
                legend([realPlot.ch1.coordinate,realPlot.ch2.coordinate,realPlot.ch3.coordinate,...
                    voiPlot.ch1.coordinate,voiPlot.ch2.coordinate,voiPlot.ch3.coordinate,...
                    strobPlot.ch13,strobPlot.ch14,strobPlot.ch15,],...
                    '������ x','������ y','������ z','��� x','��� y','��� z',...
                    '������ �� x','������ �� y','������ �� z');
            end
            
            if(chPoi == 1 && chNoize == 0 && chStrob == 1)
                poiPlot = evalin('base','poiPlot');
                strobPlot = evalin('base','strobPlot');
                legend([realPlot.ch1.coordinate,realPlot.ch2.coordinate,realPlot.ch3.coordinate,...
                    voiPlot.ch1.coordinate,voiPlot.ch2.coordinate,voiPlot.ch3.coordinate,...
                    poiPlot.ch5,poiPlot.ch6,poiPlot.ch7,...
                    strobPlot.ch13,strobPlot.ch14,strobPlot.ch15,],...
                    '������ x','������ y','������ z','��� x','��� y','��� z','��� x','��� y','��� z',...
                    '������ �� x','������ �� y','������ �� z');
            end
            
            if(chPoi == 0 && chNoize == 1 && chStrob == 1)
                noizePlot = evalin('base','noizePlot');
                strobPlot = evalin('base','strobPlot');
                legend([realPlot.ch1.coordinate,realPlot.ch2.coordinate,realPlot.ch3.coordinate,...
                    voiPlot.ch1.coordinate,voiPlot.ch2.coordinate,voiPlot.ch3.coordinate,...
                    noizePlot.ch9,noizePlot.ch10,noizePlot.ch11,...
                    strobPlot.ch13,strobPlot.ch14,strobPlot.ch15,],...
                    '������ x','������ y','������ z','��� x','��� y','��� z',...
                    '���� �� x','���� �� y','���� �� x','������ �� x','������ �� y','������ �� z');
            end
            if(chNoize == 1 && chPoi == 1 && chStrob == 1)
                noizePlot = evalin('base','noizePlot');
                strobPlot = evalin('base','strobPlot');
                poiPlot = evalin('base','poiPlot');
                legend([realPlot.ch1.coordinate,realPlot.ch2.coordinate,realPlot.ch3.coordinate,...
                    voiPlot.ch1.coordinate,voiPlot.ch2.coordinate,voiPlot.ch3.coordinate,...
                    poiPlot.ch5,poiPlot.ch6,poiPlot.ch7,...
                    noizePlot.ch9,noizePlot.ch10,noizePlot.ch11,...
                    strobPlot.ch13,strobPlot.ch14,strobPlot.ch15,],...
                    '������ x','������ y','������ z','��� x','��� y','��� z','��� x','��� y','��� z',...
                    '���� �� x','���� �� y','���� �� x','������ �� x','������ �� y','������ �� z');
            end
        case 2
            legend([realPlot.ch1.speed,realPlot.ch2.speed,realPlot.ch3.speed,...
                 voiPlot.ch1.speed,voiPlot.ch2.speed,voiPlot.ch3.speed,],...
                 '������ Vx','������ Vy','������ Vz','��� Vx','��� Vy','��� Vz' );
        case 3
            legend([realPlot.ch1.acceleration,realPlot.ch2.acceleration,realPlot.ch3.acceleration,...
                voiPlot.ch1.acceleration,voiPlot.ch2.acceleration,voiPlot.ch3.acceleration,],...
                '������ ax','������ ay','������ az','��� ax','��� ay','��� az' );     
    end