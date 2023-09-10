import express from "express"

const app = express()

app.get("/", (request, response) => {
    response.send("Hello there!")
})

// set up server exposed to other devices on the network
const port = process.env.PORT ?? 8080
app.listen(port, "10.48.153.96")