const path = require("path");
const bsconfigJson = require("./bsconfig.json");
const packageJson = require("./package.json");
const modulesToTranspile = [
  // rescript & rescript deps
  "bs-platform/package.json",
  ...bsconfigJson["bs-dependencies"].map((d) => d + "/package.json"),
  ...Object.keys(packageJson.dependencies).filter((dep) =>
    dep.startsWith("react-native")
  ),
];
const withTM = require("next-transpile-modules")(modulesToTranspile);

const config = {
  images: {
    domains: ["data.dame.bio"],
  },

  env: {
    ENV: process.env.NODE_ENV,
  },
  // target: "serverless",

  // rescript
  pageExtensions: ["jsx", "js", "bs.js"],

  webpack: (config, options) => {
    if (!options.isServer) {
      // We shim fs for things like the blog slugs component
      // where we need fs access in the server-side part
      config.node = {
        fs: "empty",
      };
    }

    // react-native-web
    config.resolve.alias = {
      ...(config.resolve.alias || {}),
      // Transform all direct `react-native` imports to `react-native-web`
      "react-native$": "react-native-web",
    };
    config.resolve.extensions = [
      ".web.js",
      ".web.ts",
      ".web.tsx",
      ...config.resolve.extensions,
    ];

    // avoid duplicated react
    // config.resolve.alias['react'] = path.resolve(__dirname, '.', 'node_modules', 'react');

    return config;
  },
};

module.exports = withTM(config);
