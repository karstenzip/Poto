import sharp from "sharp"

const SCREEN_WIDTH = 384
const SCREEN_HEIGHT = 216

export default defineEventHandler(async (event) => {
	const formData = await readMultipartFormData(event)
	if (!formData || formData.length <= 0 || formData.length > 5)
		throw createError({ status: 400 })
	const outputs: { [filename: string]: Buffer } = {}
	for (const image of formData) {
		if (!image.filename || image.filename in outputs) continue
		const buffer = await sharp(image.data)
			.resize(SCREEN_WIDTH, SCREEN_HEIGHT, { fit: "fill" })
			.removeAlpha()
			.raw()
			.toBuffer()
		// Replace extension with .bin
		image.filename = image.filename.replace(/\.\w+$/, "") + ".bin"
		outputs[image.filename] = buffer
	}
	return outputs
})
