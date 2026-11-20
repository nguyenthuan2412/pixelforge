// Node sharp side of the comparison. Usage: node bench.mjs <scenario> <iterations>
import sharp from 'sharp';
import { readFileSync } from 'node:fs';

const F = '/app/fixtures';
const [name, n] = [process.argv[2], Number(process.argv[3] ?? 20)];
if (process.env.PIXELFORGE_CONCURRENCY) sharp.concurrency(Number(process.env.PIXELFORGE_CONCURRENCY));
if (process.env.NO_CACHE) sharp.cache(false);
const buf = readFileSync(`${F}/large.jpg`);

const jobs = {
  'resize800-jpeg':   () => sharp(`${F}/large.jpg`).resize(800).jpeg({ quality: 80 }).toBuffer(),
  'resize800-webp':   () => sharp(buf).resize(800).webp({ quality: 80 }).toBuffer(),
  'cover320-sharpen': () => sharp(`${F}/large.jpg`).resize(320, 240).sharpen().jpeg().toBuffer(),
  'resize800-avif':   () => sharp(`${F}/large.jpg`).resize(800).avif({ effort: 2 }).toBuffer(),
  'reencode-full':    () => sharp(`${F}/large.jpg`).jpeg({ quality: 80 }).toBuffer(),
  'png-alpha-200':    () => sharp(`${F}/alpha.png`).resize(200).png().toBuffer(),
  'watermark-1200':   () => sharp(`${F}/large.jpg`).resize(1200).composite([{ input: `${F}/overlay.png`, gravity: 'southeast' }]).jpeg().toBuffer(),
  'mixed':            async () => { let o; for (const j of ['resize800-jpeg','resize800-webp','png-alpha-200','cover320-sharpen','reencode-full']) o = await jobs[j](); return o; },
  'metadata':         () => sharp(`${F}/large.jpg`).metadata().then(m => Buffer.from(String(m.width))),
};
const job = jobs[name];
let out = await job();
const t = process.hrtime.bigint();
for (let i = 0; i < n; i++) out = await job();
const ms = Number(process.hrtime.bigint() - t) / 1e6 / n;
const peakMB = process.resourceUsage().maxRSS / 1024;
await new Promise(r => setTimeout(r, 1500));
console.log(JSON.stringify({ name, ms, peakMB, steadyMB: process.memoryUsage().rss / 1048576, bytes: out.length }));
