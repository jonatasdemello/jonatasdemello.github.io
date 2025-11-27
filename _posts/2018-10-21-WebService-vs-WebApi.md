---
title: WebService vs WebApi
date: 2018-10-21
author: Jonatas
tags: ["code", "web"]
---


# Web Service vs Web API

What are the differences between a WebService and Web API?

Both are means of communication between consumers and providers over a network.

## Web Service

Definition from W3C:

> A Web service is a software system designed to support interoperable machine-to-machine interaction over a network. It has an interface described in a machine-processable format (specifically WSDL). Other systems interact with the Web service in a manner prescribed by its description using SOAP-messages, typically conveyed using HTTP with an XML serialization in conjunction with other Web-related standards.

Main points:

- Web Service communicate using XML.
- A client invokes a web service by sending a XML request message
- The service sends back an XML response
- SOA (service oriented architecture), rely on XML-RPC and SOAP (Simple Object Access Protocol)
- Highly coupled - the client calls a remote procedure

[w3schools](https://www.w3schools.com/xml/tempconvert.asmx?WSDL)

[dne](http://www.dneonline.com/calculator.asmx?WSDL)


## Web Api

The term "API" stands for Application Programming Interface.

In practice, an API is "a set of functions and procedures" that allow you to access and build upon the data and functionality of an existing application.

Web APIs expose an application’s data and functionality over the internet.
Web APIs usually send data back and forth using HTTP requests. These requests often return textual data in the form of a JSON or XML response.

Main points:

- Uses HTTP protocol
- The client doesn't need to know what procedure to call on the server
- HTTP verbs (GET, PUT, POST, DELETE)
- Loosely coupled
- RESTful APIs
- Data payloads can be of multiple types such as JSON or XML

Example of endpoints:

`http://api.plos.org/search?q=title:DNA`

`http://api.plos.org/search?q=title:Drosophila&fl=id,abstract`

WebAPI does not expose it's methods, I used Swagger (https://swagger.io) to generate my API documentation

Unfortunately, most of these APIs do not come with any specification that developers (and machines) can rely on to automatically understand and integrate them. Instead, most of the time we have to rely on reading its ad-hoc documentation web pages, despite the existence of languages to model Web APIs like Swagger or, more recently, OpenAPI that developers could use to formally describe their APIs.


--------


### Calling a WebService in C#

Using Visual Studio, you add a Service Reference to the WebService URL:

`http://www.dneonline.com/calculator.asmx`

This will add references to .csproj file and web.config or app.config. It will also create a file in the project:

> `"\Service References\CalculatorSvc\Reference.cs"`

describing all the methods no inside the code we instanciate the object and call the method:

```java
using WebTest.CalculatorSvc;
namespace WebTest
{
    class Program
    {
        static void Main(string[] args)
        {
            var calc = new CalculatorSoapClient();
            var res1 = calc.Add(10,20);
            Console.WriteLine("Result: "+ res);
        }
    }
}
```

Here we have to call the method

`"Add(int intA, int intB)"`


### Calling a Web API in C#

To call a web API from a .NET application, there are several ways using:

- HttpWebRequest/Response Class
- WebClient Class
- HttpClient Class
- RestSharp NuGet Package
- ServiceStack Http Utils
- Flurl

[example](https://code-maze.com/different-ways-consume-restful-api-csharp/)

Using System.Net.Http.HttpClient, endpoint:

>  `https://reqres.in/api/users`

```java
namespace WebTest
{
    public class TestApi
    {
        private static readonly HttpClient client = new HttpClient();

        public string GetUsers()
        {
            string Url = "https://reqres.in/api/users/2";
            var result = "";

            // Add an Accept header for JSON format.
            client.DefaultRequestHeaders.Accept.Clear();
            client.DefaultRequestHeaders.Accept.Add(new MediaTypeWithQualityHeaderValue("application/json"));

            var response = client.GetStringAsync(Url).Result; //blocking, I know...
            return response;
        }
    }
}
```

## Aditional Information

Url:
https://www.xtm-cloud.com/project-manager-gui/services/v2/customer/XTMWebService?wsdl

Notice the "?wsdl" at the end:

> WSDL stands for Web Services Description Language.

An WSDL document describes a web service. It specifies the location of the service, and the methods of the service, using these major elements:

- `<types>`	Defines the (XML Schema) data types used by the web service
- `<message>`	Defines the data elements for each operation
- `<portType>`	Describes the operations that can be performed and the messages involved.
- `<binding>`	Defines the protocol and data format for each port type

[W3Schools](https://www.w3schools.com/xml/xml_wsdl.asp)

[Wikipedia](https://en.wikipedia.org/wiki/Web_Services_Description_Language)



### WSDL


[WSDL](https://www.w3.org/TR/2001/NOTE-wsdl-20010315)


WSDL is an XML format for describing network services as a set of endpoints operating on messages containing either document-oriented or procedure-oriented information. The operations and messages are described abstractly, and then bound to a concrete network protocol and message format to define an endpoint. Related concrete endpoints are combined into abstract endpoints (services). WSDL is extensible to allow description of endpoints and their messages regardless of what message formats or network protocols are used to communicate, however, the only bindings described in this document describe how to use WSDL in conjunction with SOAP 1.1, HTTP GET/POST, and MIME.


### SOAP


https://en.wikipedia.org/wiki/SOAP


SOAP (originally Simple Object Access Protocol) is a messaging protocol specification for exchanging structured information in the implementation of web services in computer networks. Its purpose is to induce extensibility, neutrality and independence. It uses XML Information Set for its message format, and relies on application layer protocols, most often Hypertext Transfer Protocol (HTTP) or Simple Mail Transfer Protocol (SMTP), for message negotiation and transmission.


SOAP allows processes running on disparate operating systems (such as Windows and Linux) to communicate using Extensible Markup Language (XML). Since Web protocols like HTTP are installed and running on all operating systems, SOAP allows clients to invoke web services and receive responses independent of language and platforms.


### REST


https://en.wikipedia.org/wiki/Representational_state_transfer


Representational State Transfer (REST) is an architectural style that defines a set of constraints to be used for creating web services. Web services that conform to the REST architectural style, or RESTful web services, provide interoperability between computer systems on the Internet. REST-compliant web services allow the requesting systems to access and manipulate textual representations of web resources by using a uniform and predefined set of stateless operations. Other kinds of web services, such as SOAP web services, expose their own arbitrary sets of operations.[1]

```
https://api.example.com/resources/
	GET 	List the URIs and perhaps other details of the collection's members.
	PUT		Replace the entire collection with another collection.
	PATCH	Not generally used
	POST	Create a new entry in the collection. The new entry's URI is assigned automatically and is usually returned by the operation.[17]
	DELETE	Delete the entire collection.

https://api.example.com/resources/item17
	GET 		Retrieve a representation of the addressed member of the collection, expressed in an appropriate Internet media type.
	PUT			Replace the addressed member of the collection, or if it does not exist, create it.
	PATCH		Update the addressed member of the collection.
	POST		Not generally used. Treat the addressed member as a collection in its own right and create a new entry within it.[17]
	DELETE		Delete the addressed member of the collection.
```


### XML-RPC


https://en.wikipedia.org/wiki/XML-RPC


XML-RPC is a remote procedure call (RPC) protocol which uses XML to encode its calls and HTTP as a transport mechanism.[1] "XML-RPC" also refers generically to the use of XML for remote procedure call, independently of the specific protocol. This article is about the protocol named "XML-RPC".



### RSDL


http://www.balisage.net/Proceedings/vol10/html/Robie01/BalisageVol10-Robie01.html


RESTful Service Description Language (RSDL) provides a description of the structure and elements in the the REST API in one whole XML specification. Invoke the RSDL using the following request.


```
GET /api?rsdl HTTP/1.1
Accept: application/xml
```

Links


> https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Virtualization/3.1/html/Developer_Guide/sect-Developer_Guide.entry_Point-RSDL.html


> https://modeling-languages.com/automatic-discovery-web-api-specifications/


> https://swagger.io/resources/articles/best-practices-in-api-documentation/
https://modeling-languages.com/modeling-web-api-comparing/


References


> https://blogs.mulesoft.com/dev/api-dev/apis-versus-web-services/


> https://docs.microsoft.com/en-us/aspnet/web-api/overview/advanced/calling-a-web-api-from-a-net-client

