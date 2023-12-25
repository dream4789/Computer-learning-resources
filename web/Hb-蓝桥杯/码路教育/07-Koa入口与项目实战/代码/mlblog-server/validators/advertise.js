function advertiseValidator(ctx) {
  ctx
    .validateBody("title")
    .required("广告标题 title不能为空")
    .isString()
    .trim();
  ctx.validateBody("link").required("广告链接 link不能为空").isString().trim();
}
module.exports = {
  advertiseValidator,
};
