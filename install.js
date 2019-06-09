const os = require('os')
const { execSync: exec } = require('child_process')
const platform = os.platform()

const source = `${__dirname}/tmp`

try {
  exec(`rm -rf ${source}`, { stdio: 'ignore' })
} catch (_) {
}

function run (cmd) {
  try {
    exec(cmd, { stdio: 'ignore' })
  } catch (err) {
    console.log(err)
    process.exit(1)
  }
}

function finish () {
  run(`rm -rf ${source}`)
  process.exit(0)
}

//
// https://libsodium.gitbook.io/doc/installation
//
const url = 'https://github.com/jedisct1/libsodium'
exec(`git clone ${url} --branch stable ${source}`)

if (platform === 'linux' || platform === 'darwin') {
  run(`./configure`, { cwd: source })
  run(`make`, { cwd: source })
  run(`sudo make install`, { cwd: source })
  finish()
}

if (platform.includes('win')) {
  run(`./dist-build/msys2-win64.sh`, { cwd: source })
  finish()
}
