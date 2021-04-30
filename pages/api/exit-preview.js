export default async function exit(_, res) {
  res.clearPreviewData();
  res.writeHead(307, { Location: "/" });
  res.end();
}
