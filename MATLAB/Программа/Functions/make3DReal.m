
function make3DReal(Info,content)
Size = size(Info);

if(content == 1)
    for i = 1 : Size(2)
        sizex = size(Info(i).x);
        sizey = size(Info(i).y);
        sizez = size(Info(i).z);
        try
            Real3dPlot(i) = plot3(Info(i).x,Info(i).y,Info(i).z,'-x','LineWidth',2,...
                'Visible','off','DisplayName', "Эталон" + i);
            assignin('base','Real3dPlot',Real3dPlot);
            hold on;
            grid on;
            RealEnd3dPlot(i) = plot3(Info(i).x(sizex(2)),Info(i).y(sizey(2)),Info(i).z(sizez(2)),'o',...
                'Visible','off','DisplayName', "Конец эталона" + i);
            assignin('base','RealEnd3dPlot',RealEnd3dPlot);
            legend;
        catch
            errordlg('Нет доступных трасс');
        end
    end
else
    Real3dPlot = evalin('base','Real3dPlot');
    RealEnd3dPlot = evalin('base','RealEnd3dPlot');
    for i = 1 : Size(2)
        delete(Real3dPlot(i));
        delete(RealEnd3dPlot(i));
    end
end