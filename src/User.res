open Storage
let getName = () => Storage.store->nameGet
let setName = v => {
  store->nameSet(v)
  saveStore()
}
let getEmail = () => store->emailGet
let setEmail = v => {
  store->emailSet(v)
  saveStore()
}
let getUrl = () => store->urlGet
let setUrl = v => {
  store->urlSet(v)
  saveStore()
}
