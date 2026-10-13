// Networking protocols
// A network protocol defines rules for communication between devices

// important protocols
/**
 * TCP
 * - Reliable, Ordered byte stream
 * - Web, email, databases
 * 
 * UDP
 * - Connectionless datagrams, no delivery guarantee
 * - Gaming, discovery, realtime media
 * 
 * FTP
 * - File Transfer Protocol
 * - File Transfer
 * - Typically uses TCP
 * 
 * HTTP
 * - Application-lavel request-response protocol
 * - Web services
 * - Can operate over TCP
 * 
 * HTTPS
 * - HTTP protected using TLS
 * - Secure web API's
 */

 // TCP versus UDP
 /**
  * TCP provides reliable, ordered delivery of bytes, using mechanisms such as acknowledgement and transmission
  * - Connection oriented
  * - Reloable delivery
  * - Ordered delivery
  * - Message boundaries - Byte stream, not preserved
  * - QTcpSocket
  * 
  * UDP sends individual datagrams without guaranteeing arival ordering, or duplicate prevention
  * - Not connection oriented
  * - Not reliable, No built-in guarantee
  * - Ordered delivery - No guarantee
  * - Message boundaries - Datagrams preserved
  * - QUdpSocket
  */

// TCP client in Qt
#include <QTcpSocket>

QTcpSocket socket;

socket.connectToHost(
    "example.com",
    80
);

if (socket.waitForConnected(3000)) {
    socket.write(
        "GET / HTTP/1.1\r\n"
        "Host: example.com\r\n"
        "Connection: close\r\n\r\n"
    );

    socket.waitForReadyRead(3000);

    QByteArray response =
        socket.readAll();

    qDebug() << response;
}

//  This demonstrates a simple TCP-based HTTP request, not a complete HTTP client
// Production HTTP applications should normally use QNetworkAccessManager which handles much of the HTTP protocol complexity

// UDP communication
#include <QUdpSocket>

QUdpSocket socket;

QByteArray message = "Hello";

socket.writeDatagram(
    message,
    QHostAddress::LocalHost,
    45454
);

// A receiver can bnd to a port
QUdpSocket receiver;

receiver.bind(
    QHostAddress::LocalHost,
    45454
);

// HTTP networking with QNetworkAccessManager
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

QNetworkAccessManager* manager =
    new QNetworkAccessManager(this);

QNetworkRequest request(
    QUrl("https://example.com")
);

QNetworkReply* reply =
    manager->get(request);

connect(
    reply,
    &QNetworkReply::finished,
    this,
    [reply]() {
        if (reply->error() ==
            QNetworkReply::NoError) {

            qDebug() << reply->readAll();
        } else {
            qDebug() << reply->errorString();
        }

        reply->deleteLater();
    }
);

// Important classes
/**
 * - QNetworkAccessManager - manages HTTP requests
 * - QNetworkRequest - describes a request
 * - QNetworkReply - represents an asynchronous response
 * - QUrl - represents a resource URL
 */


//  Cloud Computing
/**
 * Provides on demand access to computing resources such as servers, storage, databases and application services over a network
 * 
 * Characteristics include
 * - On demand provision
 * - Resource pooking
 * - Elastic scaling
 * - Measured Usage
 * - Broad network access
 * 
 * Cloud service models
 * 
 * IaaS - Infrastructure as a Service
 * - The provider supplies computing infrastructure while the customer manages more of the operating system and software stack
 * - VM
 * 
 * PaaS - Platform as a Service
 * - The provider manages the application platform, allowing developers to focus on deploying applications
 * - managed application runtimes and deployment platforms
 * - Vercel, Cloudflare
 * 
 * SaaS - Software as a Service
 * - Users consume a complete application delivered as a service
 * - web based mail, document collaboration, crm systems
 */


 /**
  * Cloud deplyment models
  * 
  * Public cloud- infrastructure shared across customers though a provider
  * Private cloud - Infrastructure dedicated to one organisation
  * Hybrid Cloud - Combines private and public environments
  * Community Cloud - Shared by organisations with common requirements
  */

/**
 * Benefits
 * - elastic scaling
 * - reduced initial infrastructure investment
 * - rapid provisioning
 * - global reach
 * - managed services
 * - and potential improvements in availability
 * 
 * Challanges
 * - ongoing operation cost
 * - vendor lock-on
 * - security responsibilities
 * - network dependency
 * - latency compliance requirements
 * - and service outages
 */

/**
 * The shared responsibility model is important:
 * - cloud providers secure the infrastructure they manage, while customers remain responsible for aspects such as application configuration, access permissions, and data protection according to the service model
 */