# Twitter_top100
  At any time, the client program can be run.  It will take a
  command line parameter, which is a search term, and it will issue a query
  against the Twitter API.  It will process the result set as follows:
      Produce a histogram from the top 100 results, matching number of tweets
      to dates.  Save this in a MongoDB collection called "hist".  The query
      term should be the document name.
  - Note: query terms that are user handles (@name) or hashtags (#tag) will
    naturally show user activity or topic trends
  - Note: authentication for the Twitter API uses OAuth.  It will take some
    time for you to figure it out.  Plan accordingly.
 
  The server program should do three things.
    - It should serve an index.html file in response to GET /
    - It should serve other files in response to GET /files/<filename>
    - It should serve JSON, pulled from MongoDB, in response to GET /data/term
  With regard to the third of these tasks, "term" should be a search term, and
  the response should be a JSON representation of the histogram for that term,
  as determined by the client.  If no histogram exists, then the JSON response
  should be empty.
 
  The HTML5 component should be a single-page web app that allows the user to
  enter a search term.  In response to that term, the page will issue an AJAX
  request to the server to get some JSON data, and then it should use that JSON
  data to initialize a chart.  You can use an existing JavaScript charting
  library, such as Dygraphs, Chart.js, D3.js, etc.  You may also use other
  JavaScript libraries (jQuery, Bootstrap, etc.), as you see fit.
