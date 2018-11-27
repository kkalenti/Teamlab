% --- Создается пустая цель шума
function make3D(Info,content)
Size = size(Info);

if(content == 1)
    for i = 1 : Size(2)
        sizex = size(Info(i).x);
        sizey = size(Info(i).y);
        sizez = size(Info(i).z);
        aim3dPlot(i) = plot3(Info(i).x,Info(i).y,Info(i).z,'-x','LineWidth',2,'DisplayName', "Цель" + i);
        assignin('base','aim3dPlot',aim3dPlot);
        hold on;
        grid on;
        aimEnd3dPlot(i) = plot3(Info(i).x(sizex(2)),Info(i).y(sizey(2)),Info(i).z(sizez(2)),'o'...
            ,'DisplayName', "Конец трассы" + i);
        assignin('base','aimEnd3dPlot',aimEnd3dPlot);
        legend;
    end
elseif (content == 2)
    poi3dPlot = plot3(Info.x,Info.y,Info.z,'+','LineWidth',2,'DisplayName', "ПОИ");
    hold on;
    grid on;
    assignin('base','poi3dPlot',poi3dPlot);
elseif (content == 3)
    Noize3dPlot = plot3(Info.x,Info.y,Info.z,'+','LineWidth',2,'DisplayName', "Шумы");
    hold on;
    grid on;
    assignin('base','Noize3dPlot',Noize3dPlot);
else
    aim3dPlot = evalin('base','aim3dPlot');
    aimEnd3dPlot = evalin('base','aimEnd3dPlot');
    for i = 1 : Size(2)
        delete(aim3dPlot(i));
        delete(aimEnd3dPlot(i));
    end
end

    
   

