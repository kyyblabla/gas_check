#include "configxml.h"

#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomAttr>
#include <QtXml/QDomDocument>
#include <QtXml/QDomProcessingInstruction>
#include <QTextStream>
#include <QFile>
#include <QDebug>

QList<Addr*> ConfigXml::addrs;

ConfigXml::ConfigXml(QObject *parent) :
    QObject(parent)
{

}


void ConfigXml::init(){

    QFile file("addrConfig.xml");
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        qDebug()<<"open for read error..." ;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;

    QDomDocument doc;
    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
        qDebug()<<"setcontent error..." ;
        file.close();
    }

    file.close();

    QDomElement root = doc.documentElement();
    if (root.tagName() != "root") {
        qDebug()<<"root.tagname != ipconfig..." ;
    }

    QDomNodeList addrlist = root.childNodes();

    for(int i = 0;i < addrlist.count();i++) //for
    {
        QDomNode addrNode = addrlist.at(i);
        if(addrNode.isElement())
        {
            Addr*addr=new Addr;

            addr->index= ConfigXml::addrs.length();
            addr->id=addrNode.toElement().attribute("id").toInt();

            QDomNodeList attrlist = addrNode.toElement().childNodes();
            for(int j = 0;j < attrlist.count();j++){

                QDomNode attrNode = attrlist.at(j);

                if(attrNode.isElement())
                {
                    QString tagName=attrNode.toElement().tagName();
                    if(tagName=="startAddr"){

                        addr->startAddr=attrNode.toElement().text().toInt();

                    }else if(tagName=="numCoils"){

                        addr->coilNum=attrNode.toElement().text().toInt();
                    }else if(tagName=="num"){

                        addr->num=attrNode.toElement().text();

                    }else if(tagName=="slaveId"){

                        addr->slaveId=attrNode.toElement().text().toInt();

                    }else if(tagName=="location"){

                        addr->location=attrNode.toElement().text().toInt();

                    }else if(tagName=="telStartAddr"){

                        addr->telStartAddr=attrNode.toElement().text().toInt();

                    }else if(tagName=="telColiNum"){

                        addr->telColiNum=attrNode.toElement().text().toInt();

                    }


                }

            }

            ConfigXml::addrs.append(addr);
        }
    } //end for
}



void ConfigXml::update(){

   // qDebug()<<"open for write..." ;
    QFile file("addrConfig.xml");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug()<<"open for read write..." ;
    }

    QDomDocument doc;

    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);


    QDomElement root = doc.createElement("root");
    doc.appendChild(root);

    for(int i=0;i<addrs.length();i++){

        Addr*pAddr=addrs.at(i);

        qDebug()<<pAddr->slaveId  ;

        QDomElement addr = doc.createElement("addr");
        root.appendChild(addr);

        addr.setAttribute("id",pAddr->id);

        QDomElement startAddr=doc.createElement("startAddr");
        startAddr.appendChild(doc.createTextNode(QString::number(pAddr->startAddr)));

        QDomElement slaveId=doc.createElement("slaveId");
        slaveId.appendChild(doc.createTextNode(QString::number(pAddr->slaveId)));

        QDomElement numCoils=doc.createElement("numCoils");
        numCoils.appendChild(doc.createTextNode(QString::number(pAddr->coilNum)));

        QDomElement location=doc.createElement("location");
        location.appendChild(doc.createTextNode(QString::number(pAddr->location)));

        QDomElement num=doc.createElement("num");
        num.appendChild(doc.createTextNode( pAddr->num));

        QDomElement telStartAddr=doc.createElement("telStartAddr");
        telStartAddr.appendChild(doc.createTextNode( QString::number(pAddr->telStartAddr)));

        QDomElement telColiNum=doc.createElement("telColiNum");
        telColiNum.appendChild(doc.createTextNode( QString::number(pAddr->telColiNum)));


        addr.appendChild(startAddr);
        addr.appendChild(slaveId);
        addr.appendChild(numCoils);
        addr.appendChild(location);
        addr.appendChild(num);

        addr.appendChild(telStartAddr);
        addr.appendChild(telColiNum);


    }

    QTextStream out(&file);
    doc.save(out,4);
    file.close();


}
