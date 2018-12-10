
function make3DHypo(Info,content)
Size = size(Info);

if(content == 1)
    for i = 1 : Size(2)
        sizex = size(Info(i).x);
        sizey = size(Info(i).y);
        sizez = size(Info(i).z);
        try
            Hypo3dPlot(i) = plot3(Info(i).x,Info(i).y,Info(i).z,'-.x','LineWidth',2,...
                'Visible','off','DisplayName', "Гипотеза" + i);
            assignin('base','Hypo3dPlot',Hypo3dPlot);
            hold on;
            grid on;
            HypoEnd3dPlot(i) = plot3(Info(i).x(sizex(2)),Info(i).y(sizey(2)),Info(i).z(sizez(2)),'o'...
                ,'Visible','off','DisplayName', "Конец гипотезы" + i);
            assignin('base','HypoEnd3dPlot',HypoEnd3dPlot);
            legend;
        catch
            errordlg('Нет доступных трасс');
        end
    end
else
    Hypo3dPlot = evalin('base','Hypo3dPlot');
    HypoEnd3dPlot = evalin('base','HypoEnd3dPlot');
    for i = 1 : Size(2)
        delete(Hypo3dPlot(i));
        delete(HypoEnd3dPlot(i));
    end
end

    
   
