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

    // print data sent to the WebSocket server
    socket.on("message", data => {
        console.log("> " + data)
    })
})

// set up server exposed to other devices on the network
const port = process.env.PORT ?? 8080
http.listen(port, () => {
    console.log(`Listening at ${ip.address()}:${port}`)
})