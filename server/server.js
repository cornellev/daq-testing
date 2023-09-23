import express from "express"
import morgan from "morgan"
import { createServer } from "http"
import { WebSocketServer } from "ws"
import ip from "ip"

const app = express()
const http = createServer(app)
const server = new WebSocketServer({ server: http })

// log all requests to the server
app.use(morgan("dev"))

app.get("/", (request, response) => {
    response.send("Hello there!")
})

// when something connects to this server...
server.on("connection", socket => {
    // send socket errors to the main error stream
    socket.on("error", console.error)

    // start sending data. This is where we would want to actually
    // get the data from the mobile app instead over a *different* 
    // websocket. When we get that data, we would want to send it to
    // the frontend using this socket! This fakes having data
    const interval = setInterval(() => {
        socket.send(Math.random())
    }, 1000)

    // clear intervals if the socket closes
    socket.on("close", () => {
        clearInterval(interval)
    })
})

// set up server exposed to other devices on the network
const port = process.env.PORT ?? 8080
http.listen(port, () => {
    console.log(`Listening at ${ip.address()}:${port}`)
})