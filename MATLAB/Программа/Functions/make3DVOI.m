
function make3DVOI(Info,content)
Size = size(Info);

if(content == 1)
    for i = 1 : Size(2)
        sizex = size(Info(i).x);
        sizey = size(Info(i).y);
        sizez = size(Info(i).z);
        try
            Voi3dPlot(i) = plot3(Info(i).x,Info(i).y,Info(i).z,'--x','LineWidth',2,...
                'Visible','off','DisplayName', "ВОИ" + i);
            assignin('base','Voi3dPlot',Voi3dPlot);
            hold on;
            grid on;
            VoiEnd3dPlot(i) = plot3(Info(i).x(sizex(2)),Info(i).y(sizey(2)),Info(i).z(sizez(2)),'o'...
                ,'Visible','off','DisplayName', "Конец ВОИ" + i);
            assignin('base','VoiEnd3dPlot',VoiEnd3dPlot);
            legend;
        catch
            errordlg('Нет доступных трасс');
        end
    end
else
    Voi3dPlot = evalin('base','Voi3dPlot');
    VoiEnd3dPlot = evalin('base','VoiEnd3dPlot');
    for i = 1 : Size(2)
        delete(Voi3dPlot(i));
        delete(VoiEnd3dPlot(i));
    end
end