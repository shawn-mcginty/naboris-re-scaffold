let main = () => {
  let publicDir = Sys.getcwd() ++ "/public/";

  let conf = Naboris.ServerConfig.create()
    |> Naboris.ServerConfig.setOnListen(() => {
      print_endline("Naboris now listening on port 9000");
      print_endline("Visit http://localhost:9000");
    })
    |> Naboris.ServerConfig.addStaticMiddleware(["static"], publicDir)
    |> Naboris.ServerConfig.setRequestHandler((route, req, res) => {
      switch (Naboris.Route.meth(route), Naboris.Route.path(route)) {
        | (GET, []) | (GET, [""]) =>
          Naboris.Res.redirect("/static/index.html", req, res);
        | _ => 
          Naboris.Res.status(404, res)
          |> Naboris.Res.static(publicDir, ["not_found.html"], req);
      }
    });

    Naboris.listenAndWaitForever(9000, conf);
};

Lwt_main.run(main());