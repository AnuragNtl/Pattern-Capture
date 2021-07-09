package main

import (
	"fmt"
    //"io"
    "net/http"
)

func main() {



    http.HandleFunc("/", func(writer http.ResponseWriter, req *http.Request) {
        n := make([]byte, 1024)
        req.Body.Read(n)
        fmt.Println(string(n))
    })

    http.ListenAndServe(":8080", nil);
    // HTTP Server
}

