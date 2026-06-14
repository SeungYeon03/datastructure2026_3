#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QWidget>
#include <QString>

class MainWindow : public QMainWindow {
public:
    MainWindow() {
        setWindowTitle("놀이공원 최단경로 알리미");
        resize(500, 520);

        auto* central = new QWidget(this);
        setCentralWidget(central);
        auto* layout  = new QVBoxLayout(central);

        for(int i =0; i<10; i++) {
            for (int j = 0; j<10; j++) {
                if(i==j)
                    graph[i][j] = 0;
                else
                    graph[i][j]=INF;
            }
        }
        graph[1][2]=60;
        graph[2][1]=60;

        graph[2][3]=90;
        graph[3][2]=90;

        graph[3][4]=70;
        graph[4][3]=70;

        graph[4][5]=80;
        graph[5][4]=80;

        graph[5][7]=90;
        graph[7][5]=90;

        graph[7][8]=60;
        graph[8][7]=60;

        graph[8][9]=50;
        graph[9][8]=50;

        graph[1][9]=70;
        graph[9][1]=70;

        graph[1][6]=80;
        graph[6][1]=80;

        graph[6][5]=120;
        graph[5][6]=120;

        graph[6][8]=60;
        graph[8][6]=60;



        // 1) 이미지 (sample.jpg 를 QPixmap 으로 로드 후 라벨에 표시)
        QPixmap pixmap("map.png");
        imageLabel = new QLabel(central);
        if (pixmap.isNull()) {
            imageLabel->setText("<h3 style=color:red>sample.jpg 로드 실패</h3>");
        } else {
            imageLabel->setPixmap(pixmap.scaled(
                440, 320, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        imageLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(imageLabel);
        nodeBtn[1] = new QPushButton("1", imageLabel);
        nodeBtn[2] = new QPushButton("2", imageLabel);
        nodeBtn[3] = new QPushButton("3", imageLabel);
        nodeBtn[4] = new QPushButton("4", imageLabel);
        nodeBtn[5] = new QPushButton("5", imageLabel);
        nodeBtn[6] = new QPushButton("6", imageLabel);
        nodeBtn[7] = new QPushButton("7", imageLabel);
        nodeBtn[8] = new QPushButton("8", imageLabel);
        nodeBtn[9] = new QPushButton("9", imageLabel);

        for (int i=1; i<=9; i++) {
            nodeBtn[i] -> resize(30,30);

            nodeBtn[i] -> setStyleSheet(
                "QPushButton {"
                "background-color:white;"
                "border:2px solid black;"
                "border-radius:15px;"
                "font-weight:bold;"
                "}"
            );
        }

        nodeBtn[1]-> move(210,225);
        nodeBtn[2]-> move(70,200);
        nodeBtn[3]-> move(110,125);
        nodeBtn[4]-> move(150,70);
        nodeBtn[5]-> move(225,40);
        nodeBtn[6]-> move(225,160);
        nodeBtn[7]-> move(325,50);
        nodeBtn[8]-> move(380,130);
        nodeBtn[9]-> move(380,225);


        // 2) 카운터 라벨
        label = new QLabel("<h3 style=color:#5b3a89>가장 빠른 길을 알려드려요</h3>");
        label->setAlignment(Qt::AlignCenter);
        layout->addWidget(label);

        for (int i =1; i<=9; i++) {
            connect(nodeBtn[i],
                    &QPushButton::clicked,
                    this,
                    [this,i]() {
                for (int k=1; k<=9; k++) {
                    nodeBtn[k] ->setStyleSheet(
                        "background-color:white;"
                        "border:2px solid black;"
                        "border-radius:15px;"
                        "font-weight:bold;"
                    );

                    
                }
                if(selectCount ==0) {
                    startNode=i;
                    selectCount=1;

                    nodeBtn[i] ->setStyleSheet(
                        "background-color:lightgreen;"
                        "border:2px solid black;"
                        "border-radius:15px;"
                        "font-weight:bold;"
                    );

                    label -> setText(
                        QString("출발지 선택 : %1").arg(i)
                    );
                }
                else {
                    endNode=i;
                    nodeBtn[i] ->setStyleSheet(
                        "background-color:#ff9999;"
                        "border:2px solid black;"
                        "border-radius:15px;"
                        "font-weight:bold;"
                    );
                    selectCount=0;

                    shortestPath(startNode);
                    QString path = getPath(endNode);

                    int current = endNode;
                    while(current != -1) {
                        if(current != startNode &&
                            current != endNode)
                        {
                            nodeBtn[current] -> setStyleSheet(
                                "background-color:skyblue;"
                                "border:2px solid black;"
                                "border-radius:15px;"
                                "font-weight:bold;"
                            );
                        }
                        current = parent[current];
                    }

                    label ->setText(
                        QString(
                            "<h3 style='color:#5b3a89'>"
                            "경로 : %1<br>"
                            "거리 : %2 m"
                            "</h3>"
                        )
                        .arg(path)
                        .arg(dist[endNode])
                    );
                }
            });
        }

        }

        // 3) 버튼 → 람다로 시그널 연결 (Q_OBJECT 불필요)
     
private:
    static const int INF = 9999;

    QLabel*      imageLabel;
    QLabel*      label;
    QPushButton* nodeBtn[10];
    QString placeName[10]=
    {
        "",
        "입구",
        "성",
        "기차",
        "회전목마",
        "관람차",
        "빅탑",
        "호수",
        "롤러코스터",
        "푸드트럭"
    };

    int selectCount =0;

    int          clickCount = 0;
    int graph[10][10];
    int dist[10];
    int parent[10];
    bool found[10];

    int startNode =-1;
    int endNode = -1;

    int chooseVertex() {
        int min = INF;
        int minpos = -1;
        for (int i =1; i<=9; i++) {
            if (dist[i]<min && !found[i]) {
                min = dist[i];
                minpos =i;
            }
        }
        return minpos;
    }

    void shortestPath (int start) {
        for (int i=1; i<=9; i++){
            dist[i] = graph[start][i];
            found[i] = false;
            parent[i] = start;
        }
        found[start] = true;
        dist[start] =0;
        parent[start] =-1;

        for (int i=1; i<=9; i++) {
            int u = chooseVertex();
            if (u == -1)
                return;
            found[u] = true;
            
            for (int w=1; w<=9; w++) {
                if(!found[w]){
                    if(dist[u] + graph[u][w] < dist[w]) {
                        dist[w] = dist[u] + graph[u][w];
                        parent[w] = u;
                    }
                }
            }
        }
    }

    QString getPath (int destination) {
        QString path;
        
        int route[10];
        int count =0;

        int current = destination;

        while (current != -1) {
            route[count++] = current;
            current = parent[current];
        }
        for (int i =count-1; i>=0; i--) {
            path += placeName[route[i]];

            if(i>0)
                path += " -> ";
        }
        return path;
    }
};
