import sharp from "sharp"

export default defineEventHandler(async (event) => {
	const formData = await readMultipartFormData(event)
	if (!formData || formData.length <= 0 || formData.length > 5)
		throw createError({ status: 400 })
	const outputs: { [filename: string]: Buffer } = {}
	for (const image of formData) {
		if (!image.filename || image.filename in outputs) continue
		const buffer = await sharp(image.data)
			.resize(384, 216, { fit: "fill" })
			.removeAlpha()
			.raw()
			.toBuffer()
		// Replace extension with .bin
		image.filename = image.filename.replace(/\.\w+$/, "") + ".bin"
		outputs[image.filename] = buffer
	}
	return outputs
})
